# Spred

[Ed](https://linux.die.net/man/1/ed) is a line-based editor.  That means it does not display the text of a file outright unless you issue it a command to output some subset of the lines in a file; even then, the output does not update to cohear with further input.  This might sound like an absurdly antiquated way to edit one's files, but I have found that it provides a more beautiful experience.  Further, I find that it encourages brevity, which I consider a virtue especially while coding.  I would not necessarily recommend using Ed for large projects, but I would encourage you to look into it and see for yourself how you might fit it into your workflow.

Spred attempts to extend the structure of Ed to the editing of spreadsheets.

## Commands

```Q``` Quits the program.

```q``` Quits the program if (a) there are no unsaved changes or (b) the command has been entered twice in a row.

## Format

The file format used by Spred is extremely simple columns are divided by colons, ```:```, and rows are divided by line-breaks.  Colons employed in the spreadsheet itself are preceded by a backslash, ```\:```, and backslashes are treated similarly, ```\\```.

Once I finish the program itself, I intend to prepare a few scripts to convert between this format and more common spreadsheet formats.

## Support

At present, Spred only supports Linux, but once I have finished the program, I intend to find alternatives for the few parts of the code that shall be incompatible with Windows.