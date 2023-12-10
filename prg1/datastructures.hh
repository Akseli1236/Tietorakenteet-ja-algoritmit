// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <unordered_set>
#include <stack>

// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
using Distance = int;

// Return values for cases where required thing was not found
AffiliationID const NO_AFFILIATION = "---";
PublicationID const NO_PUBLICATION = -1;
Name const NO_NAME = "!NO_NAME!";
Year const NO_YEAR = -1;
Weight const NO_WEIGHT = -1;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};


// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: size() returns the number
    // of elements in the container
    unsigned int get_affiliation_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: clear() clears N number
    // of elements in the container
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: reserve-operation is O(1) on average
    // and loop goes iterates over unordered_map so it's O(n)
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance: O(1)
    // Short rationale for estimate: unordered_map insert() is
    // constant
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map find() is constant
    // on average and ternary operator which has comparison is also
    // constant on average
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map find() is constant
    // on average and ternary operator which has comparison is also
    // constant on average
    Coord get_affiliation_coord(AffiliationID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: std::transform operation is O(n), but
    // std:: sort operation is O(n*log(n))
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: For loop populates vector so it's O(n) and
    // std::sort operation is O(n*log(n))
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: For loop iterates through each element
    // in the map
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map find() average complexity is O(1)
    // and changing coord 'it->second.coord = newcoord' is constant
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: Complexity of unordered_map insert is O(1) and
    // function doesn't do anything else
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID> & affiliations);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Loop populating vector has time complexity O(n)
    // and reserve operation has time complexity O(1)
    std::vector<PublicationID> all_publications();

    // Estimate of performance: O(1)
    // Short rationale for estimate: unordered_map find time complexity is O(1)
    // and access to 'it->second.name' is constant time
    Name get_publication_name(PublicationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: unordered_map find time complexity is O(1)
    // and access to 'it->second.year' is constant time
    Year get_publication_year(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map find time complexity is O(1)
    // and access to 'it->second.affiliations' is constant time
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map find time complexity is O(1)
    // and checking and inserting reference to 'references' is constant
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map find time complexity is O(1)
    // and checking and getting 'references' vector is constant
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map find time complexity is O(1)
    // for both iterators and checking and inserting to both vectors are constant
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map find time complexity is O(1)
    // and checking and getting 'publications' vector is constant
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Nested loops iterates over each entry in
    // 'publications' and then 'references'
    PublicationID get_parent(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Primary loop iterates over publications and
    // the worst case for it is to found from the last.
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: Function uses nested loops and in the
    // worst case it iterates over the whole data structure
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);

    void get_referenced_by_chain_recursive(PublicationID id, std::vector<PublicationID>& references_chain, std::unordered_set<PublicationID>& visited);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    PublicationID get_closest_common_parent(PublicationID id1, PublicationID id2);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_publication(PublicationID publicationid);
    std::vector<PublicationID> get_referenced_by_chain_helper(    PublicationID id,
                                                              std::unordered_set<PublicationID>& visited);

private:

    struct Affiliation {
        AffiliationID id;
        Name name;
        Coord coord;
        std::vector<PublicationID> publications = {};
    };

    struct Publication {
        PublicationID id;
        Name name;
        Year year;
        std::vector<AffiliationID> affiliations = {};
        std::vector<PublicationID> references = {};
    };

    std::vector<std::pair<AffiliationID, Name>> vector_affiliations;

    std::unordered_map<Coord, AffiliationID, CoordHash> coord_to_affiliation;
    std::unordered_map<AffiliationID, Affiliation> affiliations = {};
    std::unordered_map<PublicationID, Publication> publications = {};
    bool sorted_aff = false;
};

#endif // DATASTRUCTURES_HH
