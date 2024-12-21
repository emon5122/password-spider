
# Password Spider

Password Spider is a tool designed to generate variations of passwords based on a wordlist. It allows you to customize the generated passwords by applying various transformations, such as converting to uppercase, capitalizing the first letter, adding numbers, or appending special characters. It also provides an option to combine each word in the wordlist with the top 10 passwords from the `pipal` password cracking tool.

## Features

- **Generate Password Variations**: Create different password variations from the input wordlist.
- **Customize Passwords**:
  - Convert all passwords to **uppercase**.
  - **Capitalize** the first letter of passwords.
  - **Add numbers** (`123`) to passwords.
  - **Add special characters** (`#$%`) to passwords.
- **Combine with Top 10 Pipal Passwords**: Combine each word from the wordlist with the top 10 passwords from the `pipal` output.
- **Help Command**: Display the usage and available flags.

## Requirements

- **GCC**: To compile the source code.
- **pipal**: A password cracking tool to generate the top 10 passwords.
- **sudo privileges**: For executing the `pipal` command.

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/emon5122/password_spider.git
   cd password_spider
   ```

2. **Install dependencies**:
   Make sure you have the `pipal` tool installed:
   ```bash
   sudo apt-get install pipal
   ```

3. **Build the project**:
   ```bash
   make
   ```

## Usage

### General Command Syntax:

```bash
./password_spider <input_file> <output_file> [flags]
```

- `<input_file>`: Path to the wordlist or password file to process.
- `<output_file>`: Path to the file where the generated passwords will be saved.

### Flags:

- `--upper`: Convert all generated passwords to uppercase.
- `--capitalize`: Capitalize the first letter of each password.
- `--add_nums`: Append the string `123` to the generated passwords.
- `--add_special`: Append the string `#$%` to the generated passwords.
- `--combine`: Combine each word from the input file with the top 10 passwords from the `pipal` output.
- `--help`: Display help and usage instructions.

### Examples:

1. **Generate passwords in uppercase with special characters**:
   ```bash
   ./password_spider input.txt output.txt --upper --add_special
   ```

2. **Combine each word from `input.txt` with the top 10 passwords from `pipal`**:
   ```bash
   ./password_spider input.txt output.txt --combine
   ```

3. **Display help**:
   ```bash
   ./password_spider --help
   ```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
