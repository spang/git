#include "userdiff.h"
#include "sigchain.h"
static int diff_suppress_blank_empty;
static const char *diff_word_regex_cfg;
static int diff_mnemonic_prefix;
	GIT_COLOR_RESET,
	GIT_COLOR_NORMAL,	/* PLAIN */
	GIT_COLOR_BOLD,		/* METAINFO */
	GIT_COLOR_CYAN,		/* FRAGINFO */
	GIT_COLOR_RED,		/* OLD */
	GIT_COLOR_GREEN,	/* NEW */
	GIT_COLOR_YELLOW,	/* COMMIT */
	GIT_COLOR_BG_RED,	/* WHITESPACE */
static void diff_filespec_load_driver(struct diff_filespec *one);
static char *run_textconv(const char *, struct diff_filespec *, size_t *);

static int git_config_rename(const char *var, const char *value)
	if (!value)
		return DIFF_DETECT_RENAME;
	if (!strcasecmp(value, "copies") || !strcasecmp(value, "copy"))
		return  DIFF_DETECT_COPY;
	return git_config_bool(var,value) ? DIFF_DETECT_RENAME : 0;
		diff_detect_rename_default = git_config_rename(var, value);
	if (!strcmp(var, "diff.mnemonicprefix")) {
		diff_mnemonic_prefix = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.wordregex"))
		return git_config_string(&diff_word_regex_cfg, var, value);
	switch (userdiff_config(var, value)) {
		case 0: break;
		case -1: return -1;
		default: return 0;
	}

	/* like GNU diff's --suppress-blank-empty option  */
	if (!strcmp(var, "diff.suppressblankempty") ||
			/* for backwards compatibility */
			!strcmp(var, "diff.suppress-blank-empty")) {
		diff_suppress_blank_empty = git_config_bool(var, value);
		return 0;
	struct strbuf res = STRBUF_INIT;
static struct diff_tempfile *claim_diff_tempfile(void) {
	int i;
	for (i = 0; i < ARRAY_SIZE(diff_temp); i++)
		if (!diff_temp[i].name)
			return diff_temp + i;
	die("BUG: diff is failing to clean up its tempfiles");
}

static int remove_tempfile_installed;

static void remove_tempfile(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(diff_temp); i++) {
		if (diff_temp[i].name == diff_temp[i].tmp_path)
			unlink_or_warn(diff_temp[i].name);
		diff_temp[i].name = NULL;
	}
}

static void remove_tempfile_on_signal(int signo)
{
	remove_tempfile();
	sigchain_pop(signo);
	raise(signo);
}

			      const char *textconv_one,
			      const char *textconv_two,
	const char *a_prefix, *b_prefix;
	const char *data_one, *data_two;
	size_t size_one, size_two;

	if (diff_mnemonic_prefix && DIFF_OPT_TST(o, REVERSE_DIFF)) {
		a_prefix = o->b_prefix;
		b_prefix = o->a_prefix;
	} else {
		a_prefix = o->a_prefix;
		b_prefix = o->b_prefix;
	}
	quote_two_c_style(&a_name, a_prefix, name_a, 0);
	quote_two_c_style(&b_name, b_prefix, name_b, 0);
	if (textconv_one) {
		data_one = run_textconv(textconv_one, one, &size_one);
		if (!data_one)
			die("unable to read files to diff");
	}
	else {
		data_one = one->data;
		size_one = one->size;
	}
	if (textconv_two) {
		data_two = run_textconv(textconv_two, two, &size_two);
		if (!data_two)
			die("unable to read files to diff");
	}
	else {
		data_two = two->data;
		size_two = two->size;
	}

	lc_a = count_lines(data_one, size_one);
	lc_b = count_lines(data_two, size_two);
		copy_file_with_prefix(o->file, '-', data_one, size_one, old, reset);
		copy_file_with_prefix(o->file, '+', data_two, size_two, new, reset);

	struct diff_words_orig {
		const char *begin, *end;
	} *orig;
	int orig_nr, orig_alloc;
	ALLOC_GROW(buffer->text.ptr, buffer->text.size + len, buffer->alloc);
	buffer->text.ptr[buffer->text.size] = '\0';
	const char *current_plus;
	regex_t *word_regex;
static void fn_out_diff_words_aux(void *priv, char *line, unsigned long len)
	struct diff_words_data *diff_words = priv;
	int minus_first, minus_len, plus_first, plus_len;
	const char *minus_begin, *minus_end, *plus_begin, *plus_end;
	if (line[0] != '@' || parse_hunk_header(line, len,
			&minus_first, &minus_len, &plus_first, &plus_len))
	/* POSIX requires that first be decremented by one if len == 0... */
	if (minus_len) {
		minus_begin = diff_words->minus.orig[minus_first].begin;
		minus_end =
			diff_words->minus.orig[minus_first + minus_len - 1].end;
	} else
		minus_begin = minus_end =
			diff_words->minus.orig[minus_first].end;
	if (plus_len) {
		plus_begin = diff_words->plus.orig[plus_first].begin;
		plus_end = diff_words->plus.orig[plus_first + plus_len - 1].end;
	} else
		plus_begin = plus_end = diff_words->plus.orig[plus_first].end;

	if (diff_words->current_plus != plus_begin)
		fwrite(diff_words->current_plus,
				plus_begin - diff_words->current_plus, 1,
				diff_words->file);
	if (minus_begin != minus_end)
		color_fwrite_lines(diff_words->file,
				diff_get_color(1, DIFF_FILE_OLD),
				minus_end - minus_begin, minus_begin);
	if (plus_begin != plus_end)
		color_fwrite_lines(diff_words->file,
				diff_get_color(1, DIFF_FILE_NEW),
				plus_end - plus_begin, plus_begin);

	diff_words->current_plus = plus_end;
}

/* This function starts looking at *begin, and returns 0 iff a word was found. */
static int find_word_boundaries(mmfile_t *buffer, regex_t *word_regex,
		int *begin, int *end)
{
	if (word_regex && *begin < buffer->size) {
		regmatch_t match[1];
		if (!regexec(word_regex, buffer->ptr + *begin, 1, match, 0)) {
			char *p = memchr(buffer->ptr + *begin + match[0].rm_so,
					'\n', match[0].rm_eo - match[0].rm_so);
			*end = p ? p - buffer->ptr : match[0].rm_eo + *begin;
			*begin += match[0].rm_so;
			return *begin >= *end;
		}
		return -1;
	/* find the next word */
	while (*begin < buffer->size && isspace(buffer->ptr[*begin]))
		(*begin)++;
	if (*begin >= buffer->size)
		return -1;
	/* find the end of the word */
	*end = *begin + 1;
	while (*end < buffer->size && !isspace(buffer->ptr[*end]))
		(*end)++;

	return 0;
/*
 * This function splits the words in buffer->text, stores the list with
 * newline separator into out, and saves the offsets of the original words
 * in buffer->orig.
 */
static void diff_words_fill(struct diff_words_buffer *buffer, mmfile_t *out,
		regex_t *word_regex)
	int i, j;
	long alloc = 0;
	out->size = 0;
	out->ptr = NULL;
	/* fake an empty "0th" word */
	ALLOC_GROW(buffer->orig, 1, buffer->orig_alloc);
	buffer->orig[0].begin = buffer->orig[0].end = buffer->text.ptr;
	buffer->orig_nr = 1;

	for (i = 0; i < buffer->text.size; i++) {
		if (find_word_boundaries(&buffer->text, word_regex, &i, &j))
			return;

		/* store original boundaries */
		ALLOC_GROW(buffer->orig, buffer->orig_nr + 1,
				buffer->orig_alloc);
		buffer->orig[buffer->orig_nr].begin = buffer->text.ptr + i;
		buffer->orig[buffer->orig_nr].end = buffer->text.ptr + j;
		buffer->orig_nr++;

		/* store one word */
		ALLOC_GROW(out->ptr, out->size + j - i + 1, alloc);
		memcpy(out->ptr + out->size, buffer->text.ptr + i, j - i);
		out->ptr[out->size + j - i] = '\n';
		out->size += j - i + 1;

		i = j - 1;
	/* special case: only removal */
	if (!diff_words->plus.text.size) {
		color_fwrite_lines(diff_words->file,
			diff_get_color(1, DIFF_FILE_OLD),
			diff_words->minus.text.size, diff_words->minus.text.ptr);
		diff_words->minus.text.size = 0;
		return;
	}
	diff_words->current_plus = diff_words->plus.text.ptr;
	memset(&xpp, 0, sizeof(xpp));
	memset(&xecfg, 0, sizeof(xecfg));
	diff_words_fill(&diff_words->minus, &minus, diff_words->word_regex);
	diff_words_fill(&diff_words->plus, &plus, diff_words->word_regex);
	xpp.flags = XDF_NEED_MINIMAL;
	/* as only the hunk header will be parsed, we need a 0-context */
	xecfg.ctxlen = 0;
	xdi_diff_outf(&minus, &plus, fn_out_diff_words_aux, diff_words,
		      &xpp, &xecfg, &ecb);
	if (diff_words->current_plus != diff_words->plus.text.ptr +
			diff_words->plus.text.size)
		fwrite(diff_words->current_plus,
			diff_words->plus.text.ptr + diff_words->plus.text.size
			- diff_words->current_plus, 1,
			diff_words->file);
		free (ecbdata->diff_words->minus.orig);
		free (ecbdata->diff_words->plus.orig);
		free(ecbdata->diff_words->word_regex);
	if (diff_suppress_blank_empty
	    && len == 2 && line[0] == ' ' && line[1] == '\n') {
		line[0] = '\n';
		len = 1;
	}

	struct strbuf name = STRBUF_INIT;
		      const char *prefix, const char *name, int len)
	fprintf(file, " %s%-*s |", prefix, len, name);
		struct strbuf buf = STRBUF_INIT;
static void show_stats(struct diffstat_t *data, struct diff_options *options)
	int i, len, add, del, adds = 0, dels = 0;
			show_name(options->file, prefix, name, len);
			show_name(options->file, prefix, name, len);
		show_name(options->file, prefix, name, len);
	       " %d files changed, %d insertions(+), %d deletions(-)\n",
	       total_files, adds, dels);
static void show_numstat(struct diffstat_t *data, struct diff_options *options)
		 * made to the preimage. In --dirstat-by-file mode, count
		 * damaged files, not damaged lines. This is done by
		 * counting only a single damaged line per file.
		if (DIFF_OPT_TST(options, DIRSTAT_BY_FILE) && damage > 0)
			damage = 1;
static void diff_filespec_load_driver(struct diff_filespec *one)
	if (!one->driver)
		one->driver = userdiff_find_by_path(one->path);
	if (!one->driver)
		one->driver = userdiff_find_by_name("default");
int diff_filespec_is_binary(struct diff_filespec *one)
	if (one->is_binary == -1) {
		diff_filespec_load_driver(one);
		if (one->driver->binary != -1)
			one->is_binary = one->driver->binary;
		else {
			if (!one->data && DIFF_FILE_VALID(one))
				diff_populate_filespec(one, 0);
			if (one->data)
				one->is_binary = buffer_is_binary(one->data,
						one->size);
			if (one->is_binary == -1)
				one->is_binary = 0;
		}
	return one->is_binary;
static const struct userdiff_funcname *diff_funcname_pattern(struct diff_filespec *one)
	diff_filespec_load_driver(one);
	return one->driver->funcname.pattern ? &one->driver->funcname : NULL;
static const char *userdiff_word_regex(struct diff_filespec *one)
	diff_filespec_load_driver(one);
	return one->driver->word_regex;
}
void diff_set_mnemonic_prefix(struct diff_options *options, const char *a, const char *b)
{
	if (!options->a_prefix)
		options->a_prefix = a;
	if (!options->b_prefix)
		options->b_prefix = b;
}
static const char *get_textconv(struct diff_filespec *one)
{
	if (!DIFF_FILE_VALID(one))
		return NULL;
	if (!S_ISREG(one->mode))
		return NULL;
	diff_filespec_load_driver(one);
	return one->driver->textconv;
	const char *a_prefix, *b_prefix;
	const char *textconv_one = NULL, *textconv_two = NULL;

	if (DIFF_OPT_TST(o, ALLOW_TEXTCONV)) {
		textconv_one = get_textconv(one);
		textconv_two = get_textconv(two);
	}

	diff_set_mnemonic_prefix(o, "a/", "b/");
	if (DIFF_OPT_TST(o, REVERSE_DIFF)) {
		a_prefix = o->b_prefix;
		b_prefix = o->a_prefix;
	} else {
		a_prefix = o->a_prefix;
		b_prefix = o->b_prefix;
	}
	a_one = quote_two(a_prefix, name_a + (*name_a == '/'));
	b_two = quote_two(b_prefix, name_b + (*name_b == '/'));
		if (complete_rewrite &&
		    (textconv_one || !diff_filespec_is_binary(one)) &&
		    (textconv_two || !diff_filespec_is_binary(two))) {
			emit_rewrite_diff(name_a, name_b, one, two,
						textconv_one, textconv_two, o);
	    ( (diff_filespec_is_binary(one) && !textconv_one) ||
	      (diff_filespec_is_binary(two) && !textconv_two) )) {
		const struct userdiff_funcname *pe;

		if (textconv_one) {
			size_t size;
			mf1.ptr = run_textconv(textconv_one, one, &size);
			if (!mf1.ptr)
				die("unable to read files to diff");
			mf1.size = size;
		}
		if (textconv_two) {
			size_t size;
			mf2.ptr = run_textconv(textconv_two, two, &size);
			if (!mf2.ptr)
				die("unable to read files to diff");
			mf2.size = size;
		}
		memset(&xpp, 0, sizeof(xpp));
		xecfg.interhunkctxlen = o->interhunkcontext;
			if (!o->word_regex)
				o->word_regex = userdiff_word_regex(one);
			if (!o->word_regex)
				o->word_regex = userdiff_word_regex(two);
			if (!o->word_regex)
				o->word_regex = diff_word_regex_cfg;
			if (o->word_regex) {
				ecbdata.diff_words->word_regex = (regex_t *)
					xmalloc(sizeof(regex_t));
				if (regcomp(ecbdata.diff_words->word_regex,
						o->word_regex,
						REG_EXTENDED | REG_NEWLINE))
					die ("Invalid regular expression: %s",
							o->word_regex);
			}
		xdi_diff_outf(&mf1, &mf2, fn_out_consume, &ecbdata,
			      &xpp, &xecfg, &ecb);
		if (textconv_one)
			free(mf1.ptr);
		if (textconv_two)
			free(mf2.ptr);
		xdiff_clear_find_func(&xecfg);
		memset(&xpp, 0, sizeof(xpp));
		xdi_diff_outf(&mf1, &mf2, diffstat_consume, diffstat,
			      &xpp, &xecfg, &ecb);
		memset(&xpp, 0, sizeof(xpp));
		xdi_diff_outf(&mf1, &mf2, checkdiff_consume, &data,
			      &xpp, &xecfg, &ecb);
	spec->is_binary = -1;
	/*
	 * We do not read the cache ourselves here, because the
	if (!FAST_WORKING_DIRECTORY && !want_file && has_sha1_pack(sha1))
	/*
	 * If ce is marked as "assume unchanged", there is no
	 * guarantee that work tree matches what we are looking for.
	 */
	if (ce->ce_flags & CE_VALID)
		return 0;

	struct strbuf buf = STRBUF_INIT;
		struct strbuf buf = STRBUF_INIT;
			struct strbuf sb = STRBUF_INIT;

			if (strbuf_readlink(&sb, s->path, s->size))
			s->size = sb.len;
			s->data = strbuf_detach(&sb, NULL);
			s->should_free = 1;
		if (size_only)
			return 0;
static void prep_temp_blob(const char *path, struct diff_tempfile *temp,
	struct strbuf buf = STRBUF_INIT;
	struct strbuf template = STRBUF_INIT;
	char *path_dup = xstrdup(path);
	const char *base = basename(path_dup);

	/* Generate "XXXXXX_basename.ext" */
	strbuf_addstr(&template, "XXXXXX_");
	strbuf_addstr(&template, base);
	fd = git_mkstemps(temp->tmp_path, PATH_MAX, template.buf,
			strlen(base) + 1);
		die_errno("unable to create temp-file");
	if (convert_to_working_tree(path,
			(const char *)blob, (size_t)size, &buf)) {
		blob = buf.buf;
		size = buf.len;
	}
		die_errno("unable to write temp-file");
	strbuf_release(&buf);
	strbuf_release(&template);
	free(path_dup);
static struct diff_tempfile *prepare_temp_file(const char *name,
		struct diff_filespec *one)
	struct diff_tempfile *temp = claim_diff_tempfile();

		return temp;
	}

	if (!remove_tempfile_installed) {
		atexit(remove_tempfile);
		sigchain_push_common(remove_tempfile_on_signal);
		remove_tempfile_installed = 1;
			die_errno("stat(%s)", name);
			struct strbuf sb = STRBUF_INIT;
			if (strbuf_readlink(&sb, name, st.st_size) < 0)
				die_errno("readlink(%s)", name);
			prep_temp_blob(name, temp, sb.buf, sb.len,
			strbuf_release(&sb);
		return temp;
		prep_temp_blob(name, temp, one->data, one->size,
	return temp;
		struct diff_tempfile *temp_one, *temp_two;
		const char *othername = (other ? other : name);
		temp_one = prepare_temp_file(name, one);
		temp_two = prepare_temp_file(othername, two);
		*arg++ = temp_one->name;
		*arg++ = temp_one->hex;
		*arg++ = temp_one->mode;
		*arg++ = temp_two->name;
		*arg++ = temp_two->hex;
		*arg++ = temp_two->mode;
		struct userdiff_driver *drv = userdiff_find_by_path(attr_path);
		if (drv && drv->external)
			pgm = drv->external;
				die_errno("stat '%s'", one->path);
				die("cannot hash %s", one->path);
	if (!diff_mnemonic_prefix) {
		options->a_prefix = "a/";
		options->b_prefix = "b/";
	}
	} else if (opt_arg(arg, 0, "dirstat-by-file",
			   &options->dirstat_percent)) {
		options->output_format |= DIFF_FORMAT_DIRSTAT;
		DIFF_OPT_SET(options, DIRSTAT_BY_FILE);
		DIFF_XDL_SET(options, IGNORE_WHITESPACE);
		DIFF_XDL_SET(options, IGNORE_WHITESPACE_CHANGE);
		DIFF_XDL_SET(options, IGNORE_WHITESPACE_AT_EOL);
	else if (!strcmp(arg, "--patience"))
		DIFF_XDL_SET(options, PATIENCE_DIFF);
	else if (!strcmp(arg, "--color-words")) {
		DIFF_OPT_SET(options, COLOR_DIFF);
		DIFF_OPT_SET(options, COLOR_DIFF_WORDS);
	}
	else if (!prefixcmp(arg, "--color-words=")) {
		DIFF_OPT_SET(options, COLOR_DIFF);
		DIFF_OPT_SET(options, COLOR_DIFF_WORDS);
		options->word_regex = arg + 14;
	}
	else if (!strcmp(arg, "--textconv"))
		DIFF_OPT_SET(options, ALLOW_TEXTCONV);
	else if (!strcmp(arg, "--no-textconv"))
		DIFF_OPT_CLR(options, ALLOW_TEXTCONV);
	else if (opt_arg(arg, '\0', "inter-hunk-context",
			 &options->interhunkcontext))
		;
	for (;;) {
	git_SHA_CTX *ctx;
	git_SHA1_Update(data->ctx, line, new_len);
	git_SHA_CTX ctx;
	git_SHA1_Init(&ctx);
		memset(&xpp, 0, sizeof(xpp));
		git_SHA1_Update(&ctx, buffer, len1);
		xdi_diff_outf(&mf1, &mf2, patch_id_consume, &data,
			      &xpp, &xecfg, &ecb);
	git_SHA1_Final(sha1, &ctx);

static char *run_textconv(const char *pgm, struct diff_filespec *spec,
		size_t *outsize)
{
	struct diff_tempfile *temp;
	const char *argv[3];
	const char **arg = argv;
	struct child_process child;
	struct strbuf buf = STRBUF_INIT;

	temp = prepare_temp_file(spec->path, spec);
	*arg++ = pgm;
	*arg++ = temp->name;
	*arg = NULL;

	memset(&child, 0, sizeof(child));
	child.argv = argv;
	child.out = -1;
	if (start_command(&child) != 0 ||
	    strbuf_read(&buf, child.out, 0) < 0 ||
	    finish_command(&child) != 0) {
		strbuf_release(&buf);
		remove_tempfile();
		error("error running textconv command '%s'", pgm);
		return NULL;
	}
	remove_tempfile();

	return strbuf_detach(&buf, outsize);
}