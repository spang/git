	"\033[m",	/* reset */
	"",		/* PLAIN (normal) */
	"\033[1m",	/* METAINFO (bold) */
	"\033[36m",	/* FRAGINFO (cyan) */
	"\033[31m",	/* OLD (red) */
	"\033[32m",	/* NEW (green) */
	"\033[33m",	/* COMMIT (yellow) */
	"\033[41m",	/* WHITESPACE (red background) */
static struct ll_diff_driver {
	const char *name;
	struct ll_diff_driver *next;
	const char *cmd;
} *user_diff, **user_diff_tail;

/*
 * Currently there is only "diff.<drivername>.command" variable;
 * because there are "diff.color.<slot>" variables, we are parsing
 * this in a bit convoluted way to allow low level diff driver
 * called "color".
 */
static int parse_lldiff_command(const char *var, const char *ep, const char *value)
	const char *name;
	int namelen;
	struct ll_diff_driver *drv;

	name = var + 5;
	namelen = ep - name;
	for (drv = user_diff; drv; drv = drv->next)
		if (!strncmp(drv->name, name, namelen) && !drv->name[namelen])
			break;
	if (!drv) {
		drv = xcalloc(1, sizeof(struct ll_diff_driver));
		drv->name = xmemdupz(name, namelen);
		if (!user_diff_tail)
			user_diff_tail = &user_diff;
		*user_diff_tail = drv;
		user_diff_tail = &(drv->next);
	}

	return git_config_string(&(drv->cmd), var, value);
}

/*
 * 'diff.<what>.funcname' attribute can be specified in the configuration
 * to define a customized regexp to find the beginning of a function to
 * be used for hunk header lines of "diff -p" style output.
 */
struct funcname_pattern_entry {
	char *name;
	char *pattern;
	int cflags;
};
static struct funcname_pattern_list {
	struct funcname_pattern_list *next;
	struct funcname_pattern_entry e;
} *funcname_pattern_list;

static int parse_funcname_pattern(const char *var, const char *ep, const char *value, int cflags)
{
	const char *name;
	int namelen;
	struct funcname_pattern_list *pp;

	name = var + 5; /* "diff." */
	namelen = ep - name;

	for (pp = funcname_pattern_list; pp; pp = pp->next)
		if (!strncmp(pp->e.name, name, namelen) && !pp->e.name[namelen])
			break;
	if (!pp) {
		pp = xcalloc(1, sizeof(*pp));
		pp->e.name = xmemdupz(name, namelen);
		pp->next = funcname_pattern_list;
		funcname_pattern_list = pp;
	}
	free(pp->e.pattern);
	pp->e.pattern = xstrdup(value);
	pp->e.cflags = cflags;
	return 0;
		if (!value)
			diff_detect_rename_default = DIFF_DETECT_RENAME;
		else if (!strcasecmp(value, "copies") ||
			 !strcasecmp(value, "copy"))
			diff_detect_rename_default = DIFF_DETECT_COPY;
		else if (git_config_bool(var,value))
			diff_detect_rename_default = DIFF_DETECT_RENAME;
	if (!prefixcmp(var, "diff.")) {
		const char *ep = strrchr(var, '.');

		if (ep != var + 4 && !strcmp(ep, ".command"))
			return parse_lldiff_command(var, ep, value);
	}
	if (!prefixcmp(var, "diff.")) {
		const char *ep = strrchr(var, '.');
		if (ep != var + 4) {
			if (!strcmp(ep, ".funcname")) {
				if (!value)
					return config_error_nonbool(var);
				return parse_funcname_pattern(var, ep, value,
					0);
			} else if (!strcmp(ep, ".xfuncname")) {
				if (!value)
					return config_error_nonbool(var);
				return parse_funcname_pattern(var, ep, value,
					REG_EXTENDED);
			}
		}
	struct strbuf res;
	strbuf_init(&res, 0);
	quote_two_c_style(&a_name, o->a_prefix, name_a, 0);
	quote_two_c_style(&b_name, o->b_prefix, name_b, 0);
	lc_a = count_lines(one->data, one->size);
	lc_b = count_lines(two->data, two->size);
		copy_file_with_prefix(o->file, '-', one->data, one->size, old, reset);
		copy_file_with_prefix(o->file, '+', two->data, two->size, new, reset);
	long current; /* output pointer */
	int suppressed_newline;
	if (buffer->text.size + len > buffer->alloc) {
		buffer->alloc = (buffer->text.size + len) * 3 / 2;
		buffer->text.ptr = xrealloc(buffer->text.ptr, buffer->alloc);
	}
	struct xdiff_emit_state xm;
static void print_word(FILE *file, struct diff_words_buffer *buffer, int len, int color,
		int suppress_newline)
	const char *ptr;
	int eol = 0;
	if (len == 0)
	ptr  = buffer->text.ptr + buffer->current;
	buffer->current += len;
	if (ptr[len - 1] == '\n') {
		eol = 1;
		len--;
	fputs(diff_get_color(1, color), file);
	fwrite(ptr, len, 1, file);
	fputs(diff_get_color(1, DIFF_RESET), file);
	if (eol) {
		if (suppress_newline)
			buffer->suppressed_newline = 1;
		else
			putc('\n', file);
	}
static void fn_out_diff_words_aux(void *priv, char *line, unsigned long len)
	struct diff_words_data *diff_words = priv;
	if (diff_words->minus.suppressed_newline) {
		if (line[0] != '+')
			putc('\n', diff_words->file);
		diff_words->minus.suppressed_newline = 0;
	}
	len--;
	switch (line[0]) {
		case '-':
			print_word(diff_words->file,
				   &diff_words->minus, len, DIFF_FILE_OLD, 1);
			break;
		case '+':
			print_word(diff_words->file,
				   &diff_words->plus, len, DIFF_FILE_NEW, 0);
			break;
		case ' ':
			print_word(diff_words->file,
				   &diff_words->plus, len, DIFF_PLAIN, 0);
			diff_words->minus.current += len;
			break;
	int i;
	minus.size = diff_words->minus.text.size;
	minus.ptr = xmalloc(minus.size);
	memcpy(minus.ptr, diff_words->minus.text.ptr, minus.size);
	for (i = 0; i < minus.size; i++)
		if (isspace(minus.ptr[i]))
			minus.ptr[i] = '\n';
	diff_words->minus.current = 0;

	plus.size = diff_words->plus.text.size;
	plus.ptr = xmalloc(plus.size);
	memcpy(plus.ptr, diff_words->plus.text.ptr, plus.size);
	for (i = 0; i < plus.size; i++)
		if (isspace(plus.ptr[i]))
			plus.ptr[i] = '\n';
	diff_words->plus.current = 0;

	xecfg.ctxlen = diff_words->minus.alloc + diff_words->plus.alloc;
	ecb.outf = xdiff_outf;
	ecb.priv = diff_words;
	diff_words->xm.consume = fn_out_diff_words_aux;
	xdi_diff(&minus, &plus, &xpp, &xecfg, &ecb);


	if (diff_words->minus.suppressed_newline) {
		putc('\n', diff_words->file);
		diff_words->minus.suppressed_newline = 0;
	}
	struct xdiff_emit_state xm;
	struct strbuf name;
	strbuf_init(&name, 0);
	struct xdiff_emit_state xm;

		      const char *prefix, const char *name, int len,
		      const char *reset, const char *set)
	fprintf(file, " %s%s%-*s%s |", set, prefix, len, name, reset);
		struct strbuf buf;
		strbuf_init(&buf, 0);
static void show_stats(struct diffstat_t* data, struct diff_options *options)
	int i, len, add, del, total, adds = 0, dels = 0;
			show_name(options->file, prefix, name, len, reset, set);
			show_name(options->file, prefix, name, len, reset, set);
		total = add + del;
			total = add + del;
		show_name(options->file, prefix, name, len, reset, set);
	       "%s %d files changed, %d insertions(+), %d deletions(-)%s\n",
	       set, total_files, adds, dels, reset);
static void show_numstat(struct diffstat_t* data, struct diff_options *options)
		 * made to the preimage.
	struct xdiff_emit_state xm;
static void setup_diff_attr_check(struct git_attr_check *check)
	static struct git_attr *attr_diff;
	if (!attr_diff) {
		attr_diff = git_attr("diff", 4);
	check[0].attr = attr_diff;
static void diff_filespec_check_attr(struct diff_filespec *one)
	struct git_attr_check attr_diff_check;
	int check_from_data = 0;
	if (one->checked_attr)
		return;

	setup_diff_attr_check(&attr_diff_check);
	one->is_binary = 0;
	one->funcname_pattern_ident = NULL;

	if (!git_checkattr(one->path, 1, &attr_diff_check)) {
		const char *value;

		/* binaryness */
		value = attr_diff_check.value;
		if (ATTR_TRUE(value))
			;
		else if (ATTR_FALSE(value))
			one->is_binary = 1;
		else
			check_from_data = 1;

		/* funcname pattern ident */
		if (ATTR_TRUE(value) || ATTR_FALSE(value) || ATTR_UNSET(value))
			;
		else
			one->funcname_pattern_ident = value;
	}

	if (check_from_data) {
		if (!one->data && DIFF_FILE_VALID(one))
			diff_populate_filespec(one, 0);

		if (one->data)
			one->is_binary = buffer_is_binary(one->data, one->size);
	}
int diff_filespec_is_binary(struct diff_filespec *one)
	diff_filespec_check_attr(one);
	return one->is_binary;
static const struct funcname_pattern_entry *funcname_pattern(const char *ident)
{
	struct funcname_pattern_list *pp;

	for (pp = funcname_pattern_list; pp; pp = pp->next)
		if (!strcmp(ident, pp->e.name))
			return &pp->e;
	return NULL;
}

static const struct funcname_pattern_entry builtin_funcname_pattern[] = {
	{ "java",
	  "!^[ \t]*(catch|do|for|if|instanceof|new|return|switch|throw|while)\n"
	  "^[ \t]*(([ \t]*[A-Za-z_][A-Za-z_0-9]*){2,}[ \t]*\\([^;]*)$",
	  REG_EXTENDED },
	{ "pascal",
	  "^((procedure|function|constructor|destructor|interface|"
		"implementation|initialization|finalization)[ \t]*.*)$"
	  "|"
	  "^(.*=[ \t]*(class|record).*)$",
	  REG_EXTENDED },
	{ "bibtex", "(@[a-zA-Z]{1,}[ \t]*\\{{0,1}[ \t]*[^ \t\"@',\\#}{~%]*).*$",
	  REG_EXTENDED },
	{ "tex",
	  "^(\\\\((sub)*section|chapter|part)\\*{0,1}\\{.*)$",
	  REG_EXTENDED },
	{ "ruby", "^[ \t]*((class|module|def)[ \t].*)$",
	  REG_EXTENDED },
};

static const struct funcname_pattern_entry *diff_funcname_pattern(struct diff_filespec *one)
	const char *ident;
	const struct funcname_pattern_entry *pe;
	int i;

	diff_filespec_check_attr(one);
	ident = one->funcname_pattern_ident;

	if (!ident)
		/*
		 * If the config file has "funcname.default" defined, that
		 * regexp is used; otherwise NULL is returned and xemit uses
		 * the built-in default.
		 */
		return funcname_pattern("default");

	/* Look up custom "funcname.$ident" regexp from config. */
	pe = funcname_pattern(ident);
	if (pe)
		return pe;

	/*
	 * And define built-in fallback patterns here.  Note that
	 * these can be overridden by the user's config settings.
	 */
	for (i = 0; i < ARRAY_SIZE(builtin_funcname_pattern); i++)
		if (!strcmp(ident, builtin_funcname_pattern[i].name))
			return &builtin_funcname_pattern[i];

	return NULL;
	a_one = quote_two(o->a_prefix, name_a + (*name_a == '/'));
	b_two = quote_two(o->b_prefix, name_b + (*name_b == '/'));
		if (complete_rewrite) {
			emit_rewrite_diff(name_a, name_b, one, two, o);
	    (diff_filespec_is_binary(one) || diff_filespec_is_binary(two))) {
		const struct funcname_pattern_entry *pe;
		ecb.outf = xdiff_outf;
		ecb.priv = &ecbdata;
		ecbdata.xm.consume = fn_out_consume;
		xdi_diff(&mf1, &mf2, &xpp, &xecfg, &ecb);
		ecb.outf = xdiff_outf;
		ecb.priv = diffstat;
		xdi_diff(&mf1, &mf2, &xpp, &xecfg, &ecb);
	data.xm.consume = checkdiff_consume;
		ecb.outf = xdiff_outf;
		ecb.priv = &data;
		xdi_diff(&mf1, &mf2, &xpp, &xecfg, &ecb);
	/* We do not read the cache ourselves here, because the
	if (!FAST_WORKING_DIRECTORY && !want_file && has_sha1_pack(sha1, NULL))
	struct strbuf buf;
	strbuf_init(&buf, 0);
		struct strbuf buf;
		if (size_only)
			return 0;
			int ret;
			s->data = xmalloc(s->size);
			ret = readlink(s->path, s->data, s->size);
			if (ret < 0) {
				free(s->data);
				goto err_empty;
			}
		strbuf_init(&buf, 0);
static void prep_temp_blob(struct diff_tempfile *temp,
	fd = git_mkstemp(temp->tmp_path, PATH_MAX, ".diff_XXXXXX");
		die("unable to create temp-file: %s", strerror(errno));
		die("unable to write temp-file");
static void prepare_temp_file(const char *name,
			      struct diff_tempfile *temp,
			      struct diff_filespec *one)
		return;
			die("stat(%s): %s", name, strerror(errno));
			int ret;
			char buf[PATH_MAX + 1]; /* ought to be SYMLINK_MAX */
			size_t sz = xsize_t(st.st_size);
			if (sizeof(buf) <= st.st_size)
				die("symlink too long: %s", name);
			ret = readlink(name, buf, sz);
			if (ret < 0)
				die("readlink(%s)", name);
			prep_temp_blob(temp, buf, sz,
		return;
		prep_temp_blob(temp, one->data, one->size,
}

static void remove_tempfile(void)
{
	int i;

	for (i = 0; i < 2; i++)
		if (diff_temp[i].name == diff_temp[i].tmp_path) {
			unlink(diff_temp[i].name);
			diff_temp[i].name = NULL;
		}
}

static void remove_tempfile_on_signal(int signo)
{
	remove_tempfile();
	signal(SIGINT, SIG_DFL);
	raise(signo);
	struct diff_tempfile *temp = diff_temp;
	static int atexit_asked = 0;
	const char *othername;
	othername = (other? other : name);
	if (one && two) {
		prepare_temp_file(name, &temp[0], one);
		prepare_temp_file(othername, &temp[1], two);
		if (! atexit_asked &&
		    (temp[0].name == temp[0].tmp_path ||
		     temp[1].name == temp[1].tmp_path)) {
			atexit_asked = 1;
			atexit(remove_tempfile);
		}
		signal(SIGINT, remove_tempfile_on_signal);
	}

		*arg++ = temp[0].name;
		*arg++ = temp[0].hex;
		*arg++ = temp[0].mode;
		*arg++ = temp[1].name;
		*arg++ = temp[1].hex;
		*arg++ = temp[1].mode;
static const char *external_diff_attr(const char *name)
{
	struct git_attr_check attr_diff_check;

	if (!name)
		return NULL;

	setup_diff_attr_check(&attr_diff_check);
	if (!git_checkattr(name, 1, &attr_diff_check)) {
		const char *value = attr_diff_check.value;
		if (!ATTR_TRUE(value) &&
		    !ATTR_FALSE(value) &&
		    !ATTR_UNSET(value)) {
			struct ll_diff_driver *drv;

			for (drv = user_diff; drv; drv = drv->next)
				if (!strcmp(drv->name, value))
					return drv->cmd;
		}
	}
	return NULL;
}

		const char *cmd = external_diff_attr(attr_path);
		if (cmd)
			pgm = cmd;
				die("stat %s", one->path);
				die("cannot hash %s\n", one->path);
	DIFF_OPT_CLR(options, DIRSTAT_CUMULATIVE);
	else
		DIFF_OPT_CLR(options, COLOR_DIFF);
	options->a_prefix = "a/";
	options->b_prefix = "b/";
		options->xdl_opts |= XDF_IGNORE_WHITESPACE;
		options->xdl_opts |= XDF_IGNORE_WHITESPACE_CHANGE;
		options->xdl_opts |= XDF_IGNORE_WHITESPACE_AT_EOL;
	else if (!strcmp(arg, "--color-words"))
		options->flags |= DIFF_OPT_COLOR_DIFF | DIFF_OPT_COLOR_DIFF_WORDS;
	for(;;) {
	struct xdiff_emit_state xm;
	SHA_CTX *ctx;
	SHA1_Update(data->ctx, line, new_len);
	SHA_CTX ctx;
	SHA1_Init(&ctx);
	data.xm.consume = patch_id_consume;
		SHA1_Update(&ctx, buffer, len1);
		ecb.outf = xdiff_outf;
		ecb.priv = &data;
		xdi_diff(&mf1, &mf2, &xpp, &xecfg, &ecb);
	SHA1_Final(sha1, &ctx);
		diffstat.xm.consume = diffstat_consume;