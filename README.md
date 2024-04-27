# Nox Database System (NDS)

        Parser for Nox Database Language (NDL) files with '.ndl' file extension.
    Splits data into groups (objects) with the aim of simplifying inheritance.
        Ultimate goal for NDS is the creation of database interface for easy
    human edition with '.ndl' files. Ultimate goal is a console tool with
    syntax checking and file editing capabilities.

## SETUP

    1. Extract 'nds.cpp' and 'ndl.h' from 'source' directory
    2. Add both files to your project as source file and header file
    3. Benefit?

## RELEASE NOTES

### VERSION PRE-RELEASE 0.2:

    - added directives:
        <template>
        <using>
    - changed structure of NDS class
    - minor syntax changes to NDL format

### VERSION PRE-RELEASE 0.1:

    - support for 5 explicit datatypes:
        int
        uint
        float
        double
        string
    - support for arrays
    - support for one-line comments
