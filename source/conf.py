# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'GEISA Specification'
copyright = 'Copyright 2025-%Y, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC'
author = 'Contributors to GEISA'
release = '0.1.0'
html_title = 'GEISA Specification'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = []

templates_path = ['_templates']
exclude_patterns = []

# -- Global Inlines ----------------------------------------------------------
# These are used throughout the docs to make it easy to add GEISA specific
# icons and headers.
# The * notation allows the html engine to use the SVG format and LaTex to use PDF
#
rst_prolog = """
.. |geisa-ee-logo| image:: images/geisa-ee-icon.*
    :alt: GEISA Execution Environment
    :height: 48pt

.. |geisa-api-logo| image:: images/geisa-api-icon.*
    :alt: GEISA Application Programming Interface
    :height: 48pt

.. |geisa-adm-logo| image:: images/geisa-adm-icon.*
    :alt: GEISA Application & Device Management
    :height: 48pt

.. |geisa-ee-hdr| image:: images/geisa-ee-header.*
    :alt: GEISA Execution Environment
    :height: 48pt

.. |geisa-api-hdr| image:: images/geisa-api-header.*
    :alt: GEISA Application Programming Interface
    :height: 48pt

.. |geisa-adm-hdr| image:: images/geisa-adm-header.*
    :alt: GEISA Application & Device Management
    :height: 48pt

.. |geisa-ee-globe| image:: images/geisa-globe-thick.*
    :alt: GEISA Execution Environment
    :width: 14pt

.. |geisa-api-gear| image:: images/geisa-gear-thick.*
    :alt: GEISA Application Programming Interface
    :width: 14pt

.. |geisa-adm-baton| image:: images/geisa-baton-thick.*
    :alt: GEISA Application & Device Management
    :width: 14pt

.. |geisa-pyramid| image:: images/geisa-pyramid.*
    :alt: GEISA Pyramid 
    :width: 20pt


"""

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'alabaster'
html_static_path = ['_static']

# -- Options for the Alabaster Theme -----------------------------------------
# https://alabaster.readthedocs.io/en/latest/customization.html

html_theme_options = {
        'logo': 'geisa-logo-small.png',
        'font_family': '-apple-system, BlinkMacSystemFont, avenir next, avenir, segoe ui, helvetica neue, Adwaita Sans, Cantarell, Ubuntu, roboto, noto, helvetica, arial, sans-serif',
        'head_font_family': '-apple-system, BlinkMacSystemFont, avenir next, avenir, segoe ui, helvetica neue, Adwaita Sans, Cantarell, Ubuntu, roboto, noto, helvetica, arial, sans-serif',
        'show_relbars': False,
        'show_relbar_bottom': True,
        'show_powered_by': False,
        }

# -- LaTex Options ------------------------------------------------------------
# Set the PDF output to assume on-line reading, rather than printing.  'openany' removes the extra
# pages the rendering engine will add otherwise.
# Use the GEISA logo.
# Use a custom style sheet to add the copyright to the pages
latex_logo = 'images/geisa-print-logo.png'
latex_additional_files = ['latex/sphinxlatexstylepage.sty']
latex_elements = {
        'extraclassoptions': 'openany',
        'preamble': r'''
\righthyphenmin=62
\lefthyphenmin=62
\usepackage[activate={true,nocompatibility},final,tracking=true,kerning=true,spacing=true,factor=1100,stretch=10,shrink=10]{microtype}
% activate={true,nocompatibility} - activate protrusion and expansion
% final - enable microtype; use "draft" to disable
% tracking=true, kerning=true, spacing=true - activate these techniques
% factor=1100 - add 10% to the protrusion amount (default is 1000)
% stretch=10, shrink=10 - reduce stretchability/shrinkability (default is 20/20)
''',
}


