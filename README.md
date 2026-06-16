# Spred

[Ed](https://linux.die.net/man/1/ed) is a line-based editor.  That means it does not display the text of a file outright unless you issue it a command to output some subset of the lines in a file; even then, the output does not update to cohear with further input.  This might sound like an absurdly antiquated way to edit one's files, but I have found that it provides a more beautiful experience.  Further, I find that it encourages brevity, which I consider a virtue especially while coding.  I would not necessarily recommend using Ed for large projects, but I would encourage you to look into it and see for yourself how you might fit it into your workflow.

Spred attempts to extend the structure of Ed to the editing of spreadsheets.

## Commands

```Q```	Quits the program.
```q```	Quits the program if (a) there are no unsaved changes or (b) the command has been entered twice in a row.