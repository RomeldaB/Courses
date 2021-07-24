(TeX-add-style-hook
 "hw5"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("geometry" "a4paper" "margin=1in" "footskip=0.25in")))
   (add-to-list 'LaTeX-verbatim-environments-local "minted")
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "inputenc"
    "amsmath"
    "amssymb"
    "amsfonts"
    "minted"
    "graphicx"
    "algorithm"
    "algorithmic"
    "titlesec"
    "geometry"
    "fancyhdr"
    "enumitem"
    "tikz")
   (TeX-add-symbols
    "coursename"
    "hwnumber"
    "Lcvy"))
 :latex)

