# specification
The GEISA Specification is an effort by the [Grid Edge Interoperability and
Security Alliance](https://lfenergy.org/projects/geisa/) to define a
consistent, secure, and interoperable computing environment for embedded
devices at the very edge of the electric utility grid, like electric meters and
distribution automation devices, for the benefit of utilities, platform
vendors, and software vendors.  If you would like to get involved, please head
over to our Wiki page for details on participation
(https://lfenergy.org/projects/geisa/).  Follow the onboarding link for details
about participating in our community process.  You are also welcome to fork
this repository and submit pull requests if you have additions or corrections
you would like considered.

GEISA maintains its formal specification as a set of reStructured text files,
which are converted to HTML via Sphinx. See
https://www.sphinx-doc.org/en/master/index.html for details on Sphinx.

Python `venv` creates a virtual environment so that Sphinx can be installed using
its own separate packages and not break anything in the existing environment.
Depending on your environment, you may need to install python `venv` using your
system package manager.

The GEISA spec also supports Mermaid diagrams.  To ensure a consistent build
process, the build scripts rely on `mmdc` and Mermaid being installed locally.
`mmdc` can be downloaded from https://github.com/mermaid-js/mermaid-cli, or
installed using `npm`.

[Mermaid](https://mermaid.js.org/) can be installed using `npm`.  `mmdc`
requires it, so `npm install -g @mermaid-js/mermaid-cli` should automatically
install it.  Please note that the `node.js` and `npm` that come with your Linux
distribution may be hopelessly out of date.  You will likely need to update
them to successfully install `mmdc`.

Here are the steps that were used from a posix environment (note, `node.js` and
`npm` updates are not shown):

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

If you are building this documentation tree from the git repository, substitute the ```mkdir specification``` with the appropriate ```git clone``` command.

Alternative make targets include `html` and `latexpdf` to build just those outputs.

To build a custom sphinx target, use `SPHINXTARGETS=foo make all`.

NOTE: Depending on your specific distribution, you may encounter errors on the LaTex file generation at the tail end of the build missing various style files such as the following:
<pre>
! LaTeX Error: File `cmap.sty' not found.
</pre>
This and other .sty files may cause build failures in LaTex generation.  

The quickest path to resolve this is to add the `texlive-latex-recommended` and `texlive-latex-extra` packages to your system.

An alternate method which may save some disk space is if your system is set up with `tlmgr` for user operation, you may be able to address each missing style file in turn via:
<pre>
tlmgr search --file --global "cmap.sty"
</pre>
which will provide the texlive package providing the specified file which can then be used to install any missing individual files.
