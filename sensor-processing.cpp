void TaskReadFlex(void *pvParameters)
{
    // https://learn.sparkfun.com/tutorials/flex-sensor-hookup-guide/all

    finger_sensor_struct *sensor = (finger_sensor_struct *)pvParameters;
    pinMode(sensor->pin, INPUT);

    // SimpleKalmanFilter(e_mea, e_est, q);
    // e_mea: Measurement Uncertainty
    // e_est: Estimation Uncertainty
    // q: Process Noise
    SimpleKalmanFilter kalman(2, 2, 0.01);

    for (;;)
    {
        // Read the ADC, and calculate voltage and resistance from it
        int raw_adc_reading = analogRead(sensor->pin);
        double flex_voltage = raw_adc_reading * M_VCC / 1023.0;
        double flex_resistance = sensor->resistance * (M_VCC / flex_voltage - 1.0);

        // Use the calculated resistance to estimate the sensor's
        // bend angle:
        double angle = map(flex_resistance, sensor->resistance_straight, sensor->resistance_bent, 0, 90.0);

        double processed = kalman.updateEstimate(angle);

        *(sensor->pvalue) = processed;

        vTaskDelay(1); // wait for one tick (15ms)
    }
}

void TaskReadForce(void *pvParameters)
{
    // https://learn.sparkfun.com/tutorials/force-sensitive-resistor-hookup-guide/all

    finger_sensor_struct *sensor = (finger_sensor_struct *)pvParameters;
    pinMode(sensor->pin, INPUT);

    // SimpleKalmanFilter(e_mea, e_est, q);
    // e_mea: Measurement Uncertainty
    // e_est: Estimation Uncertainty
    // q: Process Noise
    SimpleKalmanFilter kalman(2, 2, 0.01);

    for (;;)
    {
        double force = 0;

        int raw_adc_reading = analogRead(sensor->pin);

        // If the FSR has no pressure, the resistance will be
        // near infinite. So the voltage should be near 0.
        if (raw_adc_reading != 0) // If the analog reading is non-zero
        {
            // Use ADC reading to calculate voltage:
            double force_voltage = raw_adc_reading * M_VCC / 1023.0;

            // Use voltage and static resistor value to
            // calculate FSR resistance:
            double force_resistance = sensor->resistance * (M_VCC / force_voltage - 1.0);

            // Guesstimate force based on slopes in figure 3 of
            // FSR datasheet:
            double force_conductance = 1.0 / force_resistance; // Calculate conductance

            // Break parabolic curve down into two linear slopes:
            if (force_resistance <= 600)
                force = (force_conductance - 0.00075) / 0.00000032639;
            else
                force = force_conductance / 0.000000642857;
        }

        double processed = kalman.updateEstimate(force);

        *(sensor->pvalue) = processed;

        vTaskDelay(1); // wait for one tick (15ms)
    }
}