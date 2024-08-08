#pragma once

#include <IncludeTemplate.hpp>

// Include from kactl
#include "Point.h"
#include "sideOf.h"
#include "lineIntersection.h"

const double eps = 1e-9;

typedef Point<double> P;
typedef pair<P, P> Line;
#define L(a) a.fst, a.snd
#define PQ(a) ((a).snd - (a).fst)
vector<P> intersect(vector<Line> b){ // O(n*log(n))
	//vector<P>bx={{DINF,DINF},{-DINF,DINF},{-DINF,-DINF},{DINF,-DINF}};
	//fore(i,0,4) b.pb(halfplane(bx[i],bx[(i+1)%4]));
	sort(ALL(b), [&](Line l0, Line l1) {
		P pq0 = l0.snd - l0.fst, pq1 = l1.snd - l1.fst;
		double angle0 = atan2(pq0.y, pq0.x);
		double angle1 = atan2(pq1.y, pq1.x);
		return angle0<angle1;
	});
	int n=SZ(b),q=1,h=0;
	vector<Line> c(SZ(b)+10);
	fore(i,0,n){
		while(q < h && sideOf(L(b[i]), lineInter(L(c[h]), L(c[h-1])).snd, eps) < 0) h--;
		while(q < h && sideOf(L(b[i]), lineInter(L(c[q]), L(c[q+1])).snd, eps) < 0) q++;
		c[++h]=b[i];
		if(q<h&&abs(PQ(c[h]).cross(PQ(c[h-1])))<eps){
			if(PQ(c[h]).dot(PQ(c[h-1]))<=0) return {};
			h--;
			if(sideOf(L(b[i]), c[h].fst, eps) < 0) c[h]=b[i];
		}
	}
	while(q < h - 1 && sideOf(L(c[q]), lineInter(L(c[h]), L(c[h-1])).snd, eps) < 0)h--;
	while(q < h - 1 && sideOf(L(c[h]), lineInter(L(c[q]), L(c[q+1])).snd, eps) < 0)q++;
	if(h-q<=1)return {};
	c[h+1]=c[q];
	vector<P> s;
	fore(i,q,h+1) s.pb(lineInter(L(c[i]), L(c[i+1])).snd);
	return s;
}