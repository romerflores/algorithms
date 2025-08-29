all: teambook.pdf

codes.tex: generate_codes.py
	python3 generate_codes.py

teambook.pdf: main.tex codes.tex
	pdflatex main.tex
	pdflatex main.tex

clean:
	rm -f *.aux *.log *.out *.toc *.pdf codes.tex
