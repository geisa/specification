# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'GEISA Specification'
copyright = '2025-%Y, Grid Edge Interoperability and Security Alliance'
author = 'Grid Edge Interoperability and Security Alliance'
release = '0.1.0'
html_title = 'GEISA Specification'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = []

templates_path = ['_templates']
exclude_patterns = []

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
        }

