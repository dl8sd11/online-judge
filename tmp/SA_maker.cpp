int ws[MAXN], wv[MAXN], wa[MAXN], wb[MAXN];
bool cmp( int *r, int a, int b, int l, int n )
{ return r[a] == r[b] && r[a+l] == r[b+l]; }
void SA_maker( char* str, int* sa, int n, int m ){
       int i, p = 0, *x = wa, *y = wb;
       for( i = 0 ; i < m ; i++ ) ws[i] = 0;
       for( i = 0 ; i < n ; i++ ) ws[ (x[i] = (int)str[i]) ]++;
       for( i = 1 ; i < m ; i++ ) ws[i] += ws[i-1];
       for( i = 0 ; i < n ; i++ ) sa[ --ws[x[i]] ] = i;
       for( int l = 1 ; p < n ; l*=2, m = p ){
              // sort the second element
              for( i = n-l, p = 0 ; i < n ; i++ ) y[p++] = i;
              for( i = 0 ; i < n ; i++ ) if( sa[i] >= l ) y[p++] = sa[i]-l;
              for( i = 0 ; i < n ; i++ ) wv[i] = x[y[i]];
              // sort the first element
              for( i = 0 ; i < m ; i++ ) ws[i] = 0;
              for( i = 0 ; i < n ; i++ ) ws[wv[i]]++;
              for( i = 1 ; i < m ; i++ ) ws[i] += ws[i-1];
              for( i = n-1 ; i >= 0 ; i-- ) sa[ --ws[wv[i]] ] = y[i];
              // Get value
              swap( x, y ); x[sa[0]] = 0;
              for( i = 1, p = 1 ; i < n ; i++ )
                    x[sa[i]] = cmp( y, sa[i], sa[i-1], l, n ) ? p-1 : p++ ;
       }
}
