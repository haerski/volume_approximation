template <class Spectrahedron, class CBall>
class BallIntersectSpectra {
private:
    Spectrahedron    P;
    CBall B;
public:
    typedef typename CBall::NT NT;
    typedef typename CBall::BallPoint Point;
    typedef typename Spectrahedron::VT VT;

    BallIntersectSpectra(Spectrahedron &PP, CBall &BB) : P(PP), B(BB) {};

    Spectrahedron first() { return P; }
    CBall second() { return B; }

    int is_in(Point p){
        if(B.is_in(p)==-1)
            return P.is_in(p);
        return 0;
    }

    //int num_of_hyperplanes(){
    //    return P.num_of_hyperplanes();
   // }

    unsigned int dimension(){
        return P.dimension();
    }

    template <class SpecSettings>
    std::pair<NT,bool> boundaryOracleBilliard(VT &p, VT &v, VT &a, NT b, SpecSettings& settings, bool always_false) {

        std::pair <NT, NT> ballpair = B.line_intersect(r, v); // maybe a new class for Ball (only VT for inputs)
        Point qq(r + ballpair.first*v);
        if (P.is_in(qq)==-1){
            /* TODO update LMI according to ballpair.first and direction v */
            return std::pair<NT, bool> (ballpair.first, false);
        }

        return std::pair<NT, bool> (P.boundaryOracleBilliard(p, v, a, b, settings, false).first, false);

    }

    std::pair<NT,NT> line_intersect(Point r,
                                          Point v) {

        std::pair <NT, NT> polypair = P.line_intersect(r, v);
        std::pair <NT, NT> ballpair = B.line_intersect(r, v);
        return std::pair<NT, NT>(std::min(polypair.first, ballpair.first),
                                 std::max(polypair.second, ballpair.second));
    }

    //First coordinate ray shooting intersecting convex body
    std::pair<NT,NT> line_intersect_coord(Point &r,
                                          unsigned int rand_coord,
                                          std::vector<NT> &lamdas) {

        std::pair <NT, NT> polypair = P.line_intersect_coord(r, rand_coord, lamdas);
        std::pair <NT, NT> ballpair = B.line_intersect_coord(r, rand_coord);
        return std::pair<NT, NT>(std::min(polypair.first, ballpair.first),
                                 std::max(polypair.second, ballpair.second));
    }

    //Not the first coordinate ray shooting intersecting convex body
    std::pair<NT,NT> line_intersect_coord(Point &r,
                                          Point &r_prev,
                                          unsigned int rand_coord,
                                          unsigned int rand_coord_prev,
                                          std::vector<NT> &lamdas) {

        std::pair <NT, NT> polypair = P.line_intersect_coord(r, r_prev, rand_coord, rand_coord_prev, lamdas);
        std::pair <NT, NT> ballpair = B.line_intersect_coord(r, rand_coord);
        return std::pair<NT, NT>(std::min(polypair.first, ballpair.first),
                                 std::max(polypair.second, ballpair.second));
    }

    std::pair<NT,NT> query_dual(Point &p, unsigned int rand_coord) {
        std::pair <NT, NT> polypair = P.query_dual(p, rand_coord);
        std::pair <NT, NT> ballpair = B.line_intersect_coord(p, rand_coord);
        return std::pair<NT, NT>(std::min(polypair.first, ballpair.first),
                                 std::max(polypair.second, ballpair.second));
    }

};
