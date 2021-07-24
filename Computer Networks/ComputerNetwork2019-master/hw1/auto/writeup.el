(TeX-add-style-hook
 "writeup"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "11pt")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("fontenc" "T1") ("ulem" "normalem")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art11"
    "inputenc"
    "fontenc"
    "graphicx"
    "grffile"
    "longtable"
    "wrapfig"
    "rotating"
    "ulem"
    "amsmath"
    "textcomp"
    "amssymb"
    "capt-of"
    "hyperref")
   (LaTeX-add-labels
    "sec:org74f849f"
    "sec:orgd5588f1"
    "sec:org02b15c2"
    "sec:orgf1705fd"
    "sec:org9fcf433"
    "sec:orgc1752eb"
    "sec:orgd00d542"
    "sec:orge5085f2"
    "sec:org750d320"
    "sec:orgfd8e4cf"
    "sec:orgcb4fe5b"
    "sec:orgc94b463"
    "sec:org1fe9b27"
    "sec:org262535f"
    "sec:org17414ad"
    "sec:org0de6b76"
    "sec:org88cde30"
    "sec:org94cef85"))
 :latex)

