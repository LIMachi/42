find . -name "*.sh" | rev | cut -f1 -d"/" | cut -c4- | rev
