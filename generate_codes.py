import os

base = "."  # la raíz donde están todas las subcarpetas

with open("codes.tex", "w") as out:
    for root, dirs, files in os.walk(base):
        # Ignorar archivos en la raíz si quieres solo carpetas
        if root == ".":
            continue

        # Nombre de la sección según la carpeta
        rel_path = os.path.relpath(root, base)
        section_name = rel_path.replace("_", " ").title()
        out.write(f"\\section*{{{section_name}}}\n\n")

        # Archivos C++
        for file in sorted(files):
            if file.endswith(".cpp"):
                name = file.replace(".cpp", "")
                out.write(f"\\subsection*{{{name}}}\n")
                out.write("\\begin{lstlisting}\n")
                file_path = os.path.join(root, file)
                with open(file_path, "r", encoding="utf-8") as f:
                    out.write(f.read())
                out.write("\\end{lstlisting}\n\n")
