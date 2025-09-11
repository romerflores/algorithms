import os

base = "."  # la raíz donde están todas las subcarpetas

ignore_dirs = {".git", "__pycache__",".github",".vscode"}  # carpetas a ignorar
ignore_files = {".DS_Store", ".pdf", ".md"}  # archivos a ignorar

with open("codes.tex", "w", encoding="utf-8") as out:
    for root, dirs, files in os.walk(base):
        # Ignorar carpetas no deseadas
        dirs[:] = [d for d in dirs if d not in ignore_dirs]

        # Ignorar la raíz si quieres solo subcarpetas
        if root == ".":
            continue

        # Nombre de la sección según la carpeta
        rel_path = os.path.relpath(root, base)
        section_name = rel_path.replace("_", " ").title()
        out.write(f"\\section*{{{section_name}}}\n\n")

        # Archivos C++
        for file in sorted(files):
            if file.endswith(".cpp") and file not in ignore_files:
                name = file.replace(".cpp", "")
                out.write(f"\\subsection*{{{name}}}\n")
                out.write("\\begin{lstlisting}\n")
                file_path = os.path.join(root, file)
                with open(file_path, "r", encoding="utf-8") as f:
                    out.write(f.read())
                out.write("\\end{lstlisting}\n\n")
