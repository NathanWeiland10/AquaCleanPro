import sys
import datetime

extensions = ['sphinx_simplepdf', 
              'breathe', 
              'myst_parser', 
              'sphinx_rtd_theme' ]

# Read from rst and md files
source_suffix = ['.rst', '.md']

root_doc = 'index'

project = 'AquaClean Pro'
copyright = '2023'
author = 'Ethan Heilein, Thomas McGuff, Nermeen Saleh, Ethan Timpe, Nathaniel Weiland'
show_authors = True
version = '0.0.1'
release = 'test'

breathe_projects = {"AquaClean Pro": "./xml"}
breathe_default_project = "AquaClean Pro"

# HTML theming
html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
html_theme_options = {
    'titles_only': True
}

# PDF theming
simplepdf_vars = {
    'primary-opaque': 'rgba(35, 196, 250, 1)',
    'primary': '#23C4FA',
    'secondary': '#23C4FA',
    'cover': '#ffffff',
    'white': '#ffffff',
    'links': '#23C4FA',
    'cover-bg': 'url(pool.jpg) no-repeat center',
    'cover-overlay': 'rgba(35, 196, 250, 0.5)',
    'top-left-content': 'counter(page)',
    'bottom-center-content': '"AquaClean Pro Docs"'
}
html_context = {
    'cover_footer': f'Build: {datetime.datetime.now().strftime("%m.%d.%Y")}<br>'
                    f'Ethan Heinlein, Thomas McGuff, Nermeen Saleh, Ethan Timpe, Nathaniel Weiland'
}
simplepdf_file_name = "AquaClean-Pro.pdf"

def setup(app):
    app.add_css_file('theme.css')