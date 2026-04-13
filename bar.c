void
drawbar(Monitor *m)
{
	int x, w, tw = 0;
	int barh = barwinheight();
	int barw = barwinwidth(m);
	int boxs = drw->fonts->h / 9;
	int boxw = drw->fonts->h / 6 + 2;
	unsigned int i, occ = 0, urg = 0;
	Client *c;

	if (!m->showbar)
		return;

	/* draw status first so it can be overdrawn by tags later */
	if (m == selmon) { /* status is only drawn on selected monitor */
		drw_setscheme(drw, scheme[SchemeStatus]);
		tw = TEXTW(stext) - lrpad + 2; /* 2px right padding */
		drw_text(drw, barw - tw, 0, tw, barh, 0, stext, 0);
	}

	for (c = m->clients; c; c = c->next) {
		occ |= c->tags;
		if (c->isurgent)
			urg |= c->tags;
	}
	x = 0;
	for (i = 0; i < LENGTH(tags); i++) {
		w = TEXTW(tags[i]);
		drw_setscheme(drw, scheme[m->tagset[m->seltags] & 1 << i ? SchemeTagsSel : SchemeTagsNorm]);
		drw_text(drw, x, 0, w, barh, lrpad / 2, tags[i], urg & 1 << i);
		if (occ & 1 << i)
			drw_rect(drw, x + boxs, boxs, boxw, boxw,
				m == selmon && selmon->sel && selmon->sel->tags & 1 << i,
				urg & 1 << i);
		x += w;
	}
	w = TEXTW(m->ltsymbol);
	drw_setscheme(drw, scheme[SchemeTagsNorm]);
	x = drw_text(drw, x, 0, w, barh, lrpad / 2, m->ltsymbol, 0);

	if ((w = barw - tw - x) > barh) {
		if (m->sel) {
			drw_setscheme(drw, scheme[m == selmon ? SchemeInfoSel : SchemeInfoNorm]);
			drw_text(drw, x, 0, w, barh, lrpad / 2 + (m->sel->icon ? m->sel->icw + ICONSPACING : 0), m->sel->name, 0);
			if (m->sel->icon)
				drw_pic(drw, x + lrpad / 2, (barh - m->sel->ich) / 2, m->sel->icw, m->sel->ich, m->sel->icon);
			if (m->sel->isfloating)
				drw_rect(drw, x + boxs, boxs, boxw, boxw, m->sel->isfixed, 0);
		} else {
			drw_setscheme(drw, scheme[SchemeInfoNorm]);
			drw_rect(drw, x, 0, w, barh, 1, 1);
		}
	}
	drw_map(drw, m->barwin, 0, 0, barw, barh);
}

void
drawbars(void)
{
	Monitor *m;

	for (m = mons; m; m = m->next)
		drawbar(m);
}
