			p->path = (char*) &(p->parent[num_parent]);
		struct lline *last_one = NULL;
		/* We cannot squash it with earlier one */
		for (lline = sline->lost_head;
		     lline;
		     lline = lline->next)
			if (lline->parent_map & this_mask)
				last_one = lline;
		lline = last_one ? last_one->next : sline->lost_head;
	struct xdiff_emit_state xm;

		if (!state->nb)
			/* @@ -1,2 +0,0 @@ to remove the
			 * first two lines...
			 */
			state->nb = 1;
		if (state->nn == 0)
		else
	ecb.outf = xdiff_outf;
	ecb.priv = &state;
	state.xm.consume = consume_line;
	xdi_diff(&parent_file, result_file, &xpp, &xecfg, &ecb);
		struct sline *sl = &sline[lno];
			sl = &sline[lno++];
			size_t len = xsize_t(st.st_size);
			result_size = len;
			result = xmalloc(len + 1);
			if (result_size != readlink(elem->path, result, len)) {
			result[len] = 0;
				die("read error '%s'", elem->path);
				struct strbuf buf;
				strbuf_init(&buf, 0);
			dump_quoted_path("--- ", opt->a_prefix, elem->path,
			dump_quoted_path("+++ ", opt->b_prefix, elem->path,
		hashcpy((unsigned char*)(parent + num_parent),