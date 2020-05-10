/*
 * honestly I was just implementing this code to make sure that the solution is right , but I thought it is a Tle code but surprisingly it passed
 * http://usaco.org/current/data/sol_mooriokart_platinum_feb19.html
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 340
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
ll N , M , X , Y , K ;
vpi V [1509] ;
unordered_map < ll , ll > PathSum [1509] , PathNum [1509] ;
vi Who ;
int Timer = 1 , Done [1509] ;
ll Dp [1509][2509] , Num [1509][2509] ;
void Fill ( int Node ) {
        Who .pb ( Node ) ;
        Done [ Node ] = 1;
        for ( auto u : V [Node] ) {
                if ( Done [ u.fi ] ) C ;
                Fill ( u.fi ) ;
        }
}
void Dfs ( int Node , int P , int St , int Dis ) {
        ll RetDis = min ( (ll) Dis , Y ) ; 
        if ( St < Node ) PathNum [Timer][RetDis] ++ , PathSum [Timer][RetDis] += Dis ; 
        for ( auto u : V [Node] ) {
                if ( u.fi == P ) C ;
                Dfs ( u.fi , Node , St , Dis + u.se ) ;
        }
}
int main () {
        freopen ("mooriokart.in" , "r" , stdin ) ;
        freopen ("mooriokart.out", "w" , stdout) ;
        cin >> N >> M >> X >> Y ;
        K = N - M ;
        for ( int i = 0 ; i < M ; i ++ ) {
                int A , B , Cost ;
                cin >> A >> B >> Cost ;
                A -- , B -- ;
                V [A] .pb ( { B , Cost } ) ;
                V [B] .pb ( { A , Cost } ) ;
        }
        for ( int i = 0 ; i < N ; i ++ ) {
                if ( Done [i] ) C ;
                Who.clear () ;
                Fill ( i ) ;
                for ( auto u : Who ) Dfs ( u , u , u , 0 ) ;
                Timer ++ ;
        } 
        Dp [0][ min ( Y , K * X ) ] += K * X ;
        Num[0][ min ( Y , K * X ) ] ++ ;
        for ( ll i = 1 ; i <= K ; i ++ ) {
                for ( ll j = 0 ; j <= Y ; j ++ ) {
                        for ( auto u : PathNum [i] ) {
                                ll Len = u.fi , Ways = u.se , Sum = PathSum [i][u.fi] , J = min ( Y , j + Len ) ;
                                Dp [i][J] += Dp [i-1][j] * Ways + Sum * Num [i-1][j] ;
                                Num[i][J] += Num [i-1][j] * Ways ;
                                Dp [i][J] %= mod ;
                                Num[i][J] %= mod ;
                        }
                }
        }
        for ( ll i = 0 ; i < K - 1 ; i ++ ) Dp [K][Y] *= 2 , Dp [K][Y] %= mod ;
        for ( ll i = 1 ; i < K     ; i ++ ) Dp [K][Y] *= i , Dp [K][Y] %= mod ;
        cout << Dp [K][Y] << endl ;
}
