# specification
The GEISA Specification

The documentation was created using the Sphinx documentation tool.  Python venv creates a virtual environment so that Sphinc can be installed using its own separate packages and not break anything in the existing environment.

Here are the steps that were used:

<pre>```bash
$ mkdir specification

$ cd specification

$ python3 -m venv venv

source venv/bin/activate

(venv) $ pip3 install sphinx

(venv) $ make html

(venv) $ make latexpdf

```</pre>

If you are building this documentation tree from the git repository, substitute the ```mkdir specification``` with the appropriate ```git clone``` command.
