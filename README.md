
# GEISA Specification

## Getting Started

### What is this?

The GEISA Specification is an effort by the
[GEISA project](https://lfenergy.org/projects/geisa/)
to define a consistent, secure, and interoperable computing environment for
embedded devices at the very edge of the electric utility grid, like electric
meters and distribution automation devices, for the benefit of utilities,
platform vendors, and software vendors. See the
[GEISA project page](https://lfenergy.org/projects/geisa/) for information
about participating in the community. You are also welcome to fork this
repository and submit pull requests with additions or corrections for
consideration.

GEISA maintains its formal specification as a set of reStructuredText files
that are built into HTML and PDF using
[Sphinx](https://www.sphinx-doc.org/en/master/). See the
[Sphinx documentation](https://www.sphinx-doc.org/en/master/) for details.

The repository also includes the GEISA machine-readable definitions under
[`schemas/`](schemas/), including Protocol Buffer definitions, JSON Schemas,
profiles, examples, nanopb support, and related tooling.

### How is it licensed?

The GEISA specification and documentation are licensed under the Community
Specification License. Content under [`schemas/`](schemas/), including schemas,
examples, and related tooling, is licensed under the Apache License 2.0; see
[`schemas/LICENSE`](schemas/LICENSE).

### How can I use this?

#### Just the spec

If you're just interested in the specification itself, headover to the [GEISA
Specification](https://spec.geisa-energy.org) to access both formal releases of
the GEISA specification and nightly builds with the latest changes.  The spec
is available as both PDF and HTML.

#### Contributing

If you want to contribute to the specification or build your own implementation
of GEISA, you'll want to be able to generate the specification and the schema
examples locally.  This requires a host environment capable of running standard
POSIX tools.  Linux, MacOS, and WSL on Windows are suitable.  See below for
details on how to setup your environment.

## Setting up your own build environment

### External tools for the specification

Building the specification requires several external tools:

- Mermaid
- Draw.IO
- rsvgconvert
- LaTex

Mermaid is used for sequence diagrams and other simple generated diagrams.
diagrams.net/draw.io is used for selected layout-sensitive architecture and
similar diagrams. To ensure a consistent build process, the build scripts rely
on `mmdc` for Mermaid diagrams and `drawio` for diagrams.net/draw.io diagrams.

#### Mermaid

Mermaid requires `node.js` and can be installed using the node package manager.
The `node.js` and `npm` packages supplied by some Linux distributions may be
too old to install current Mermaid CLI releases.  As a result, you may need to
update `node.js` and `npm` before mermaid can be installed.

Install Mermaid CLI with `npm`:

```bash
npm install -g @mermaid-js/mermaid-cli
```

See the [Mermaid CLI repository](https://github.com/mermaid-js/mermaid-cli)
for additional information.

#### Draw.IO

diagrams.net/draw.io is not installed through the Python virtual environment
and does not have an official npm package equivalent to Mermaid CLI at this
time. Install draw.io Desktop using the package appropriate for your operating
system, and ensure the `drawio` command is available on `PATH`.

For Linux, use the official draw.io Desktop package for your distribution
(`.deb`, `.rpm`, or AppImage), or another trusted system package source. If
using an AppImage, create a wrapper or symlink named `drawio` somewhere in
`PATH`.  Information on the
[draw.io Desktop Package](https://www.drawio.com/doc/faq/offline) may be
found in the draw.io offline FAQ.

For example, on Ubuntu or another Debian-based distribution, download the
official draw.io Desktop `.deb` package, then install it with:

<pre>
$ sudo apt install ./drawio-amd64-<version>.deb
$ drawio --help
</pre>

Replace `<version>` with the appropriate version string from the
downloaded package name.

If you prefer to do a single-user install without modifying system packages,
download the official draw.io Desktop AppImage release instead. Place it under
a user-local directory, make it executable, and create a wrapper named `drawio`
somewhere in your user `PATH`:

<pre>
$ mkdir -p "$HOME/.local/opt/drawio" "$HOME/.local/bin"
$ cp drawio-x86_64-<version>.AppImage "$HOME/.local/opt/drawio/"
$ chmod +x "$HOME/.local/opt/drawio/drawio-x86_64-<version>.AppImage"
$ cat > "$HOME/.local/bin/drawio" <<'EOF'
#!/usr/bin/env bash
exec "$HOME/.local/opt/drawio/drawio-x86_64-<version>.AppImage" "$@"
EOF
$ chmod +x "$HOME/.local/bin/drawio"
$ export PATH="$HOME/.local/bin:$PATH"
$ drawio --help
</pre>

If `$HOME/.local/bin` is not already in your shell startup `PATH`, add it to
your shell profile before building the specification, or use another user-level
bin directory already on `PATH`.

Some Linux systems may not have FUSE configured for AppImage execution. If the
AppImage does not run directly, extract it and update the wrapper to call the
extracted `AppRun` binary:

<pre>
$ cd "$HOME/.local/opt/drawio"
$ ./drawio-x86_64-<version>.AppImage --appimage-extract
$ cat > "$HOME/.local/bin/drawio" <<'EOF'
#!/usr/bin/env bash
exec "$HOME/.local/opt/drawio/squashfs-root/AppRun" "$@"
EOF
$ chmod +x "$HOME/.local/bin/drawio"
$ drawio --help
</pre>

For macOS or others, install the official draw.io/diagrams.net Desktop
application directly. If it does not provide a `drawio` command on `PATH`,
create a user-local wrapper or symlink to the application binary.
For example:

```bash
mkdir -p "$HOME/bin"
ln -s "/Applications/draw.io.app/Contents/MacOS/draw.io" "$HOME/bin/drawio"
export PATH="$HOME/bin:$PATH"
drawio --help
```

Depending on the installed application name, the macOS binary may instead be:

<pre>
/Applications/diagrams.net.app/Contents/MacOS/diagrams.net
</pre>

#### rsvgconvert

Building the specification PDF requires
[rsvg-convert](https://gitlab.gnome.org/GNOME/librsvg).  It's part of the GNOME
project. Most Linux distributions have this; it just needs to be installed.

#### LaTex

Building the specification PDF requires [LaTex](https://www.latex-project.org/).
Most distributions have this; it just needs to be installed.

### External tools for the schemas

Building the schema examples requires several external tools:

- protoc
- nanopb

#### protoc

Protoc is a [protobuf](https://github.com/protocolbuffers/protobuf) compiler.
Most Linux distributions have this. It and the associated libraries and headers
need to be installed.

#### nanopb

[nanopb](https://github.com/nanopb/nanopb) is a protobuf compiler for C focused
on constrained environments. This can be installed manually.
Alternatively, the `setup-dev` target will prompt you to install it in `/tmp`.
See below and `schemas/README.md` for additional details.

## Cloning the repo

If you want to build the examples or the specification locally on your machine,
start by cloning this repo, including sub-modules.  (GEISA uses a sub-module to
pull in the required LwM2M schema files from the OMA GitHub repository).  For
example, to clone the main GEISA specification repo, use:

```bash
git clone --recurse-submodules https://github.com/geisa/specification.git
```

Do note the `--recurse-submodules`.  GEISA uses a Git submodule for relevant
OMA objects from the [LwM2M
Registry](https://github.com/OpenMobileAlliance/lwm2m-registry).  Because this
content is provided via a submodule, it is **not** populated by a plain `git
clone` and the directory will appear empty until the submodule is initialized.
Failing to include `--recurse-submodules` will result in build errors.

If you have already cloned the repository, without recursing submodules, fetch
the submodule from the repository root with:

```bash
git submodule update --init source/adm/external/lwm2m-registry
```

Refer to [`source/adm/external/README.md`](source/adm/external/README.md) for
additional information on GEISA OMA objects.

## Getting the base development environment setup

Building the GEISA specification requires `sphinx` as well as `GitPython`
`sphinxcontrib-svg2pdfconverter` and `linuxdoc`.  If you already have these in
your environment, things might build, but by default GEISA uses Python `venv`
to create a virtual environment so that Sphinx can be installed using its own
separate packages and not break anything in the existing environment.

Note: depending on your environment, you may need to install
Python `venv` using your system package manager first.

The GEISA `setup-dev` target will create local Python `venv` environments for
both `specification` and `schema` and automatically load much of what you'll
need into them.  It will also address Node.js development dependencies.

```bash
make setup-dev
```

## Building the specification

Assuming you've installed the required external tools, you should now be able
to build the specification.  Typing `make` by itself will provide a list of
available build targets.  `make all` will build both the PDF and html versions
of the specification.  Output can be found in `build/html` and `build/latexpdf`.

```bash
make all
```

Alternative make targets include `html` and `latexpdf` to build just those
outputs.

To build a custom Sphinx target, use `SPHINXTARGETS=foo make all`.

NOTE: Running multiple jobs as part of make (i.e. `-j 4`) may result in errors
in the `latexpdf` build.

NOTE: Depending on your specific distribution, you may encounter errors during
LaTeX file generation near the end of the build due to missing style files such
as the following:

<pre>
! LaTeX Error: File `cmap.sty' not found.
</pre>

This and other .sty files may cause build failures in LaTex generation.

The quickest path to resolve this is to add the
`texlive-latex-recommended` and `texlive-latex-extra` packages to your system.

An alternate method which may save some disk space is if your system is set up
to be used with `tlmgr` for user operation, you may be able to address each
missing style file in turn via:

<pre>
tlmgr search --file --global "cmap.sty"
</pre>

which will provide the texlive package providing the specified file which can
then be used to install any missing individual files.

## Building the schema examples

When `make setup-dev` completes, it will prompt you to install `nanopb` if it's
not already installed.

```bash
test -d /tmp/nanopb/.git || git clone https://github.com/nanopb/nanopb /tmp/nanopb
```

Once this is done, you can start building examples:

```bash
make schemas-examples-c
```

Build with `make schemas` or `make schemas-all`, clean with `make
schemas-clean`, and lint with `make schemas-lint`. Example targets are
available from the repository root as `make schemas-examples`, `make
schemas-examples-c`, and `make schemas-demos`.

See `schemas/README.md` for additional details.
