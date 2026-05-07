
# specification

The GEISA Specification is an effort by the
[GEISA project](https://lfenergy.org/projects/geisa/)
to define a consistent, secure, and interoperable computing environment for
embedded devices at the very edge of the electric utility grid, like electric
meters and distribution automation devices, for the benefit of utilities,
platform vendors, and software vendors. If you would like to get involved,
please head over to our Wiki page for details on participation:
[onboarding link](https://lfenergy.org/projects/geisa/).
Follow the onboarding link for details about participating in our community
process. You are also welcome to fork this repository and submit pull requests
if you have additions or corrections you would like considered.

GEISA maintains its formal specification as a set of reStructured text files,
which are converted to HTML via
[Sphinx](https://www.sphinx-doc.org/en/master/index.html). See the
[Sphinx documentation](https://www.sphinx-doc.org/en/master/index.html) for
details on Sphinx.

Python `venv` creates a virtual environment so that Sphinx can be installed
using its own separate packages and not break anything in the existing
environment. Depending on your environment, you may need to install python
`venv` using your system package manager.

The GEISA spec also supports generated diagrams. Mermaid is used for sequence
diagrams and other simple generated diagrams. diagrams.net/draw.io is used for
selected layout-sensitive architecture and similar diagrams.

To ensure a consistent build process, the build scripts rely on `mmdc` for
Mermaid diagrams and `drawio` for diagrams.net/draw.io diagrams.

`mmdc` can be downloaded from
[the Mermaid CLI repository](https://github.com/mermaid-js/mermaid-cli), or
installed using `npm`.

[Mermaid](https://mermaid.js.org/) can be installed using `npm`. `mmdc`
requires it, so `npm install -g @mermaid-js/mermaid-cli` should automatically
install it. Please note that the `node.js` and `npm` that come with your Linux
distribution may be hopelessly out of date. You will likely need to update
them to successfully install `mmdc`.

diagrams.net/draw.io is not installed through the Python virtual environment
and does not have an official npm package equivalent to Mermaid CLI at this
time. Install draw.io Desktop using the package appropriate for your operating
system, and ensure the `drawio` command is available on `PATH`.

For Linux, use the official draw.io Desktop package for your distribution
(`.deb`, `.rpm`, or AppImage), or another trusted system package source. If
using an AppImage, create a wrapper or symlink named `drawio` somewhere in
`PATH`.  Information on the draw.io Desktop Package may be found
[here](https://www.drawio.com/doc/faq/offline) .

For example, on Ubuntu or another Debian-based distribution, download the
official draw.io Desktop `.deb` package, then install it with:

<pre>
$ sudo apt install ./drawio-amd64-&lt;version&gt;.deb
$ drawio --help
</pre>

Replace `&lt;version&gt;` with the appropriate version string from the
downloaded package name.

If you prefer to do a single-user install without modifying system packages,
download the official draw.io Desktop AppImage release instead. Place it under
a user-local directory, make it executable, and create a wrapper named `drawio`
somewhere in your user `PATH`:

<pre>
$ mkdir -p "$HOME/.local/opt/drawio" "$HOME/.local/bin"
$ cp drawio-x86_64-&lt;version&gt;.AppImage "$HOME/.local/opt/drawio/"
$ chmod +x "$HOME/.local/opt/drawio/drawio-x86_64-&lt;version&gt;.AppImage"
$ cat > "$HOME/.local/bin/drawio" <<'EOF'
#!/usr/bin/env bash
exec "$HOME/.local/opt/drawio/drawio-x86_64-&lt;version&gt;.AppImage" "$@"
EOF
$ chmod +x "$HOME/.local/bin/drawio"
$ export PATH="$HOME/.local/bin:$PATH"
$ drawio --help
</pre>

If `$HOME/.local/bin` is not already in your shell startup `PATH`, add it to
your shell profile before building the specification (or use an existing
user-level bin path already existing).

Some Linux systems may not have FUSE configured for AppImage execution. If the
AppImage does not run directly, extract it and update the wrapper to call the
extracted `AppRun` binary:

<pre>
$ cd "$HOME/.local/opt/drawio"
$ ./drawio-x86_64-&lt;version&gt;.AppImage --appimage-extract
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

<pre>
mkdir -p "$HOME/bin"
ln -s "/Applications/draw.io.app/Contents/MacOS/draw.io" "$HOME/bin/drawio"
export PATH="$HOME/bin:$PATH"
drawio --help
</pre>

Depending on the installed application name, the macOS binary may instead be:

<pre>
/Applications/diagrams.net.app/Contents/MacOS/diagrams.net
</pre>

Here are the steps that were used from a posix environment (note, `node.js`
and `npm` updates are not shown):

<pre>
$ sudo apt install latexmk librsvg2-bin # or your package manager of choice

$ npm install -g @mermaid-js/mermaid-cli

$ mkdir specification

$ cd specification

$ python3 -m venv venv

source venv/bin/activate

(venv) $ pip3 install GitPython sphinx sphinxcontrib-svg2pdfconverter

(venv) $ make all

</pre>

If you are building this documentation tree from the git repository,
substitute the ```mkdir specification``` with the appropriate
```git clone``` command.

Alternative make targets include `html` and `latexpdf` to build just those
outputs.

To build a custom sphinx target, use `SPHINXTARGETS=foo make all`.

NOTE: Depending on your specific distribution, you may encounter errors on the
LaTex file generation at the tail end of the build missing various style files
such as the following:

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
