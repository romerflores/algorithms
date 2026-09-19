import os

base = "."

ignore_dirs = {".git", "__pycache__", ".github", ".vscode"}
ignore_files = {".DS_Store", ".pdf", ".md"}

with open("codes.tex", "w", encoding="utf-8") as out:
    for root, dirs, files in os.walk(base):
        dirs[:] = [d for d in dirs if d not in ignore_dirs]

        if root == ".":
            continue

        rel_path = os.path.relpath(root, base)
        section_name = rel_path.replace("_", " ").title()

        out.write(f"\\section{{{section_name}}}\n\n")

        for file in sorted(files):
            if file.endswith(".cpp") and file not in ignore_files:
                name = file.replace(".cpp", "")

                # Escapar caracteres especiales
                name = name.replace("_", "\\_")

                out.write(f"\\subsection{{\\texttt{{{name}}}}}\n")
                out.write("\\begin{lstlisting}\n")

                file_path = os.path.join(root, file)

                with open(file_path, "r", encoding="utf-8") as f:
                    out.write(f.read())

                out.write("\\end{lstlisting}\n\n")