# specification
The GEISA Specification

GEISA, the Grid Edge Interoperability and Security Alliance (https://lfenergy.org/projects/geisa/) maintains its formal specification as a set of reStructured text files, which are converted to HTML via Sphinx. See https://www.sphinx-doc.org/en/master/index.html for details on Sphinx.

Python venv creates a virtual environment so that Sphinx can be installed using its own separate packages and not break anything in the existing environment.  Depending on your environment, you may need to install python venv using your system package manager.

Here are the steps that were used from a posix environment:

<pre>
$ mkdir specification

$ cd specification

$ python3 -m venv venv

source venv/bin/activate

(venv) $ pip3 install sphinx

(venv) $ make html

(venv) $ make latexpdf

</pre>

If you are building this documentation tree from the git repository, substitute the ```mkdir specification``` with the appropriate ```git clone``` command.
