Code Conventions
==================

Introduction
============

This document outlines the coding conventions to be followed for this project. Adhering to these conventions ensures consistency, readability, and maintainability of the codebase.

Acknowledgment
==============

This coding convention document is inspired by and partially derived from the [MicroPython project](https://github.com/Infineon/micropython/blob/ports-psoc6-main/CODECONVENTIONS.md). We acknowledge and thank the MicroPython community for their contributions.

Git commit conventions
======================

Each commit message should start with a directory or full file path
prefix, so it was clear which part of codebase a commit affects. If
a change affects one file, it's better to use path to a file. If it
affects few files in a subdirectory, using subdirectory as a prefix
is ok. For longish paths, it's acceptable to drop intermediate
components, which still should provide good context of a change.
It's also ok to drop file extensions.

Besides prefix, first line of a commit message should describe a
change clearly and to the point, and be a grammatical sentence with
final full stop. First line must fit within 72 characters. Examples
of good first line of commit messages:

    py/objstr: Add splitlines() method.
    py: Rename FOO to BAR.
    docs/machine: Fix typo in reset() description.
    ports: Switch to use lib/foo instead of duplicated code.

After the first line add an empty line and in the following lines describe
the change in a detail, if needed, with lines fitting within 75 characters
(with an exception for long items like URLs which cannot be broken). Any
change beyond 5 lines would likely require such detailed description.

To get good practical examples of good commits and their messages, browse
the `git log` of the project.

When committing you must sign-off your commit by adding "Signed-off-by:"
line(s) at the end of the commit message, e.g. using `git commit -s`.  You
are then certifying and signing off against the following:

* That you wrote the change yourself, or took it from a project with
  a compatible license (in the latter case the commit message, and possibly
  source code should provide reference where the implementation was taken
  from and give credit to the original author, as required by the license).
* That you are allowed to release these changes to an open-source project
  (for example, changes done during paid work for a third party may require
  explicit approval from that third party).
* Your contribution including commit message will be publicly and
  indefinitely available for anyone to access, including redistribution
  under the terms of the project's license.
* Your signature for all of the above, which is the "Signed-off-by" line,
  includes your full real name and a valid and active email address by
  which you can be contacted in the foreseeable future.

Code auto-formatting
====================

C and C++ code is formatted using `clang-format` and added to Pre-Commit Hooks.
The configurarion file is stored in `config/clang-format/.clang-format`. 
However, we do not recommend that you run clang-format manually.
Please refer to the following section about Pre-Commit Hooks. 

Automatic Pre-Commit Hooks
==========================

To have code formatting and commit message conventions automatically checked,
a configuration file is provided for the [pre-commit](https://pre-commit.com/)
tool.

First install `pre-commit`, either from your system package manager or via
`pip`. When installing `pre-commit` via pip, it is recommended to use a
virtual environment. Other sources, such as Brew are also available, see
[the docs](https://pre-commit.com/index.html#install) for details.

```
$ apt install pre-commit       # Ubuntu, Debian
$ pacman -Sy python-precommit  # Arch Linux
$ brew install pre-commit      # Brew
$ pip install pre-commit       # PyPI
```

Then, inside the repository, register the git hooks for pre-commit
by running:

```
$ pre-commit install --hook-type pre-commit --hook-type commit-msg
```

pre-commit will now automatically run during `git commit` for both code and
commit message formatting.

The same formatting checks will be run by CI for any Pull Request submitted. 
Pre-commit allows you to see any failure more quickly, and in many
cases will automatically correct it in your local working copy.

To unregister `pre-commit` from your repository, run:

```
$ pre-commit uninstall --hook-type pre-commit --hook-type commit-msg
```

Tips:

* To skip pre-commit checks on a single commit, use `git commit -n` (for
  `--no-verify`).
* To ignore the pre-commit message format check temporarily, start the commit
  message subject line with "WIP" (for "Work In Progress").

Running pre-commit manually
===========================

Once pre-commit is installed as per the previous section it can be manually
run against the codebase to update file formatting on demand, with either:
* `pre-commit run --all-files` to fix all files in the codebase
* `pre-commit run --file ./path/to/my/file` to fix just one file
* `pre-commit run --file ./path/to/my/folder/*` to fix just one folder
