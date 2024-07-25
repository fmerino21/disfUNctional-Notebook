/*
Se tiene para sumas pero se puede modificar para hacer queries sobre maximos, xor, etc, la clave es que es lo que guarda los nodos que no son hojas
*/
template <typename type>
struct SegmentTree {
    int n;
    vector<type> lazy;
    vector<type> t; 

    SegmentTree(vector<type> &a) {
        this->n = a.size();

        t.resize(4 * n + 5);
        lazy.resize(4 * n + 5, 0);
        
        build(a, 1, 0, n - 1);
    }

    void build(vector<type> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = t[v*2] + t[v*2 + 1];
        }
    }
    
    void push(int v) {
        t[v*2] += lazy[v];
        lazy[v*2] += lazy[v];
        t[v*2+1] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
    }

    void update(int i, type addend) {
        update(1, 0, n - 1, i, i, addend);
    }

    void update(int l, int r, type addend) {
        update(1, 0, n - 1, l, r, addend);
    }
    
    void update(int v, int tl, int tr, int l, int r, type addend) {
        if (l > r) 
            return;
        if (l == tl && tr == r) {
            t[v] += addend;
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = t[v*2] + t[v*2+1];
        }
    }

	type query(int i) {
		return query(i, i);
	}
    
    type query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
    
    type query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && tr == r){
            return t[v];
        }
        push(v);
        int tm = (tl + tr) / 2;
        return query(v*2, tl, tm, l, min(r, tm)) + query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
};