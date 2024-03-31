# Nox Database System (NDS)

    Parser for Nox Database Language (NDL) files with '.ndl' file extension.
    Splits data into groups (objects) with the aim of simplifying inheritance.
    Ultimate goal for NDS is the creation of database interface for easy
    human edition with '.ndl' files then compiled to Nox Database Binary (NDB),
    files with '.ndb' file extension. Because of that NDS focuses on read speed with write
    speed to '.ndl' being abysmal.

## SETUP

    1. Extract 'nds.cpp' and 'ndl.h' from [Source directory](source)
    2. Add both files to your project as source file and header file
    3. Benefit?

## RELEASE NOTES

### VERSION 0.1 PRE-RELEASE:

    - support for 5 explicit datatypes:
        int
        uint
        float
        double
        string
    - support for arrays
    - support for one-line comments
