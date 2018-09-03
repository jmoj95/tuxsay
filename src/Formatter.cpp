#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Formatter.hpp>

Formatter::Formatter()
{
	char text[] = "";
	this->text = text;
}

Formatter::Formatter(char *text)
{
	this->text = text;
}

Formatter::~Formatter()
{
	if (this->text)
		free(this->text);
}

void Formatter::pump(FILE *input_stream)
{
	char c;
	char *text;
	int i = 1;
	while((c = fgetc(input_stream)) != EOF)
		++i;
	text = static_cast<char *>(malloc(i * sizeof(*text)));
	if (text) {
		i = 0;
		rewind(input_stream);
		while ((c = fgetc(input_stream)) != EOF)
			text[i++] = c;
		text[i] = '\0';
	}
	this->text = text;
}

void Formatter::sink(FILE *output_stream)
{
	int i = 0;
	while (this->text[i] != '\0')
		fputc(this->text[i++], output_stream);
}

Formatter Formatter::upperCase()
{
	int i;
	char *text;
	for (i = 1; this->text[i] != '\0'; ++i);
	text = static_cast<char *>(malloc(i * sizeof(this->text)));
	for (i = 0; this->text[i] != '\0'; ++i)
		text[i] = toupper(this->text[i]);
	text[i] = '\0';
	Formatter fmtr(text);
	return fmtr;
}

Formatter Formatter::lowerCase()
{
	int i;
	char *text;
	for (i = 1; this->text[i] != '\0'; ++i);
	text = static_cast<char *>(malloc(i * sizeof(this->text)));
	for (i = 0; this->text[i] != '\0'; ++i)
		text[i] = tolower(this->text[i]);
	text[i] = '\0';
	Formatter fmtr(text);
	return fmtr;
}

Formatter Formatter::baloon()
{
	int i, j, k;
	int lines = 0, cols = 0, maxcols = 0;
	int line_offset = 4, col_offset = 4;
	char *text = NULL;
	char **temp = NULL;

	for (i = 0; this->text[i] != '\0'; ++i) {
		switch (this->text[i]) {
		case '\n':
			++lines;
			++cols;
			if (cols > maxcols)
				maxcols = cols;
			cols = 0;
			break;
		case '\t':
			cols += 4;
			break;
		default:
			++cols;
			break;
		}
	}

	temp = static_cast<char **>(malloc(lines * sizeof(*temp)));
	for (i = 0; i < lines; ++i)
		temp[i] = static_cast<char *>(malloc(maxcols * sizeof(*temp[i])));

	for (i = j = k = 0; this->text[i] != '\0'; ++i) {
		switch (this->text[i]) {
		case '\n':
			temp[j][k] = '\0';
			++j;
			k = 0;
			break;
		case '\t':
			temp[j][k++] = ' ';
			temp[j][k++] = ' ';
			temp[j][k++] = ' ';
			temp[j][k++] = ' ';
			break;
		default:
			temp[j][k++] = this->text[i];
			break;
		}
	}

	text = static_cast<char *>(malloc(((lines + line_offset) * (maxcols + col_offset) + 1) * sizeof(*text)));
	if (text) {
		for (i = 0; i < maxcols + col_offset - 1; ++i)
			text[i] = '*';
		text[i++] = '\n';
	
		text[i++] = '*';
		text[i++] = ' ';
		for (j = i; j - i < maxcols - 1; ++j)
			text[j] = ' ';
		i = j;
		text[i++] = ' ';
		text[i++] = '*';
		text[i++] = '\n';

		for (j = 0; j < lines; ++j) {
			text[i++] = '*';
			text[i++] = ' ';
			for (k = 0; temp[j][k] != '\0'; ++k)
				text[i++] = temp[j][k];
			if (k < maxcols)
				for (; k < maxcols - 1; ++k)
					text[i++] = ' ';
			text[i++] = ' ';
			text[i++] = '*';
			text[i++] = '\n';
		}

		text[i++] = '*';
		text[i++] = ' ';
		for (j = i; j - i < maxcols - 1; ++j)
			text[j] = ' ';
		i = j;
		text[i++] = ' ';
		text[i++] = '*';
		text[i++] = '\n';

		for (j = i; j - i < maxcols + col_offset - 1; ++j)
			text[j] = '*';
		i = j;
		text[i++] = '\n';
		text[i] = '\0';

		for (i = 0; i < lines; ++i)
			free(temp[i]);
		free(temp);
	}

	Formatter fmtr(text);
	return fmtr;
}

Formatter Formatter::tuxSay()
{
	int i, j, n;
	char c;
	char *text = NULL;
	char *line = NULL;
	char *tux = NULL;

	FILE *fp = fopen("characters/tux", "r");
	if (fp) {
		n = 0;
		while ((c = fgetc(fp)) != EOF)
			++n;

		tux = static_cast<char *>(malloc((n + 1) * sizeof(*tux)));

		i = 0;
		rewind(fp);
		while ((c = fgetc(fp)) != EOF)
			tux[i++] = c;
		tux[i] = '\0';
	}

	for (i = 0; this->text[i] != '\n'; ++i);
	++i;

	line = static_cast<char *>(malloc((3 * n + 1) * sizeof(*line)));	
	n = i;
	for (i = 0; i < n / 2; ++i)
		line[i] = ' ';
	line[i++] = '/';
	for (; i < n - 1; ++i)
		line[i] = ' ';
	line[i++] = '\n';

	for (j = i; j - i < n / 2 - 1; ++j)
		line[j] = ' ';
	line[j++] = '/';

	for (i = j; j - i < n - 1; ++j)
		line[j] = ' ';
	line[j++] = '\n';

	for (i = j; j - i < n / 2 - 2; ++j)
		line[j] = ' ';
	line[j++] = '/';

	for (i = j; j - i < n - 1; ++j)
		line[j] = ' ';
	line[j++] = '\n';

	line[j] = '\0';

	text = static_cast<char *>(malloc((strlen(this->text) + 1 + strlen(tux) + 1 + strlen(line) + 1) * sizeof(*text)));
	if (text) {
		for (i = 0; this->text[i] != '\0'; ++i)
			text[i] = this->text[i];
		text[i++] = '\n';
		for (j = 0; line[j] != '\0'; ++i, ++j)
			text[i] = line[j];
		text[i++] = '\n';
		for (j = 0; tux[j] != '\0'; ++i, ++j)
			text[i] = tux[j];
		text[i] = '\0';
	}

	free(tux);
	free(line);

	Formatter fmtr(text);
	return fmtr;
}
