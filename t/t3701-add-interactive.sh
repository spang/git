if ! test_have_prereq PERL; then
	say 'skipping git add -i tests, perl not available'
	test_done
fi
