			p->path = (char *) &(p->parent[num_parent]);
	struct lline *next_lost;
		lline = sline->next_lost;
				sline->next_lost = lline->next;
	sline->next_lost = NULL;
		if (state->nn == 0) {
			 *
			 * Note that this is correct even when N == 0,
			 * in which case the hunk removes the first
			 * line in the file.
			if (!state->nb)
				state->nb = 1;
		} else {
		}
		state->lost_bucket->next_lost = state->lost_bucket->lost_head;
	memset(&xpp, 0, sizeof(xpp));
	xdi_diff_outf(&parent_file, result_file, consume_line, &state,
		      &xpp, &xecfg, &ecb);
			struct sline *sl = &sline[lno++];
	const char *a_prefix, *b_prefix;
	a_prefix = opt->a_prefix ? opt->a_prefix : "a/";
	b_prefix = opt->b_prefix ? opt->b_prefix : "b/";

			struct strbuf buf = STRBUF_INIT;

			if (strbuf_readlink(&buf, elem->path, st.st_size) < 0) {
			result_size = buf.len;
			result = strbuf_detach(&buf, NULL);
				die_errno("read error '%s'", elem->path);
				struct strbuf buf = STRBUF_INIT;
			dump_quoted_path("--- ", a_prefix, elem->path,
			dump_quoted_path("+++ ", b_prefix, elem->path,
		hashcpy((unsigned char *)(parent + num_parent),