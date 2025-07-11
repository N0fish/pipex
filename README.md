<img title="42_pipex" alt="42_pipex" src="./subject/banner.png" width="100%">

|          Grade           |                           |
|:------------------------:|:-------------------------:|
| ![](./subject/grade.png) | ![](./subject/detail.png) |
	
<br>

---

<details>
<summary>🇫🇷 FRENCH VERSION</summary>

<p align="center">
    Ceci est un <a href="./subject/Pipex.fr.subject.pdf">projet</a> réalisé en avril 2024 à l'école 42.
</p>

## Préambule
Ce projet est une introduction pratique au mécanisme des `pipes` en UNIX. Il s’agit de reproduire le comportement de la commande shell suivante :

Mandatory
```shell
< file1 cmd1 | cmd2 > file2
```
Bonuses
```shell
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
cmd << LIMITER | cmd1 >> file
```

## Compétences :
- Compréhension des appels systèmes UNIX (`pipe`, `fork`, `dup2`, `execve`, etc.)
- Manipulation de processus et redirection de flux (`access`, `open`, `close`, `read`, `write`, etc.)
- Gestion fine des erreurs (`perror`, `strerror`)
- Utilisation de la variable d’environnement (`env`) (par exemple, `PATH`) pour localiser les commandes

## Installation
```bash
git clone https://github.com/N0fish/pipex.git
cd pipex
make
```

## Utilisation
```bash
./pipex infile "cmd1" "cmd2" outfile
```

## Bonus
- Support de `multiples pipes` (cmd1 | cmd2 | cmd3 ...)
```bash
make bonus
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```


- Support du mode `here_doc`
```bash
./pipex here_doc LIMITER cmd cmd1 file
```

</details>

---

<details>
<summary>🇬🇧 ENGLISH VERSION</summary>

<p align="center">
    This is a <a href="./subject/Pipex.en.subject.pdf">project</a> completed in April 2024 at 42 School.
</p>

## Preamble
This project offers a hands-on approach to UNIX `pipes`. The goal is to recreate the behavior of the following shell command:

Mandatory
```shell
< file1 cmd1 | cmd2 > file2
```
Bonuses
```shell
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
cmd << LIMITER | cmd1 >> file
```

## Skills:
- Deep understanding of UNIX system calls (`pipe`, `fork`, `dup2`, `execve`, etc.)
- Process creation and stream redirection (`access`, `open`, `close`, `read`, `write`, etc.)
- Robust error handling (`perror`, `strerror`)
- Use of environment variable (`env`) (e.g. `PATH`) to resolve commands

## Installation
```bash
git clone https://github.com/N0fish/pipex.git
cd pipex
make
```

## Usage
```bash
./pipex infile "cmd1" "cmd2" outfile
```

## Bonus
- Support for `multiple` chained `pipes` (cmd1 | cmd2 | cmd3 ...)
```bash
make bonus
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```


- `here_doc` functionality
```bash
./pipex here_doc LIMITER cmd cmd1 file
```

</details>

---

<details>
<summary>🇷🇺 RUSSIAN VERSION</summary>

<p align="center">
    Это <a href="./subject/Pipex.en.subject.pdf">проект</a>, выполненный в апреле 2024 года в школе 42.
</p>

## Преамбула
Цель — реализовать работу UNIX-механизма каналов (`pipes`), воспроизводя поведение следующей команды оболочки:

Мандатори
```shell
< file1 cmd1 | cmd2 > file2
```
Бонусы
```shell
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
cmd << LIMITER | cmd1 >> file
```

### Навыки:
- Работа с системными вызовами UNIX (`pipe`, `fork`, `dup2`, `execve` и др.)
- Управление процессами и перенаправлением ввода/вывода (`access`, `open`, `close`, `read`, `write` и др.)
- Обработка ошибок (`perror`, `strerror`)
- Использование переменной окружения (`env`) (например, `PATH`) для поиска команд


## Установка
```bash
git clone https://github.com/N0fish/pipex.git
cd pipex
make
```

## Использование
```bash
./pipex infile "cmd1" "cmd2" outfile
```

## Бонус
- Поддержка `нескольких` команд через `пайпы` (cmd1 | cmd2 | cmd3 ...)
```bash
make bonus
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

- Поддержка режима `here_doc`
```bash
./pipex here_doc LIMITER cmd cmd1 file
```

</details>

---

<br>