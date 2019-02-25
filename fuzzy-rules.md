# Fuzzy Rules

## Inputs

* index finger flex
* middle finger flex
* ring finger flex
* pinky finger flex
* thumb grip force
* index finger grip force

## Output

* thumb flex target

## Flex Fuzzy Sets

* not flexed (0, 0, , )
* partially flexed (, , , )
* half flexed (, , , )
* mostly flexed (, , , )
* fully flexed (, , , )

*Range: 0-100 degrees*

## Grip Force Fuzzy Sets

* no grip pressure (0, 0, , )
* light grip pressure (, , , )
* medium grip pressure (, , , )
* high grip pressure (, , , )

*Range: 0-N grams*

## Rules

1. `index not flexed` + `middle not flex` + `ring not flexed` + `pinky not flexed` + `thumb no grip pressure` + `index no grip pressure` -> `not flexed`
2.
