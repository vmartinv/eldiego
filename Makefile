all: eldiego.pdf

AUX_EXTS:= aux|nav|snm|log|toc|vrb|dvi|idx|fdb_latexmk|fls|out|ilg|ind


%.pdf: %.tex
		latexmk -pdf -pdflatex="pdflatex -interactive=nonstopmode" -use-make -cd  $<
		find $(dir $<) -maxdepth 1 -regextype posix-extended -regex '.*\.(${AUX_EXTS})' -delete

clean:
		find . -name '*.pdf' -delete
