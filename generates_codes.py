import os

base = "algorithms"

with open("codes.tex", "w") as out:
    for root, dirs, files in os.walk(base):
        # Tomamos solo las carpetas (graphs, maths, etc.)
        rel = os.path.relpath(root, base)
        if rel == ".":
            continue
        section = rel.replace("_", " ").title()
        out.write(f"\\section*{{{section}}}\n")
        
        for filename in sorted(files):
            if filename.endswith(".cpp"):
                out.write(f"\\subsection*{{{filename}}}\n")
                out.write("\\begin{lstlisting}\n")
                with open(os.path.join(root, filename)) as f:
                    out.write(f.read())
                out.write("\\end{lstlisting}\n\n")
