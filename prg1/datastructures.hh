// Datastructures.hh
//
// Student name:
// Student email:
// Student number:

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>

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

// Define affiliation and publication struct
struct Affiliation
{
    AffiliationID id_a;
    Name name;
    Coord coord;
};

struct Publication
{
    PublicationID id_p;
    Name title;
    Year year;
    std::vector<AffiliationID> affiliations;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:O(1)
    // Short rationale for estimate:unordered_map is a hash table structure
    unsigned int get_affiliation_count();

    // Estimate of performance:O(n)
    // Short rationale for estimate:add or delete one element into unordered_map is O(1),this operation delete n elements
    void clear_all();

    // Estimate of performance:O(n)
    // Short rationale for estimate:traverse all n elements in unordered_map
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance:O(1)
    // Short rationale for estimate:add one element into unordered_map is O(1)
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance:O(n)
    // Short rationale for estimate:search one element with key in unordered_map is O(n)
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate:search one element with key in unordered_map is O(n)
    Coord get_affiliation_coord(AffiliationID id);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:O(n*log(n))
    // Short rationale for estimate:For the traversal of an unordered_map is O(n) and sort for vector is O(n*log(n)). So in general, for the whole function it is O(n*log(n))
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance:O(n*log(n))
    // Short rationale for estimate:For the traversal of an unordered_map and a vector is O(n) and sort for vector is O(n*log(n)). So in general, for the whole function it is O(n*log(n))
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance:O(n)
    // Short rationale for estimate:traversal of an unordered_map is O(n)
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance:O(n)
    // Short rationale for estimate:search an element with key in unordered_map is O(n)
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:O(n)
    // Short rationale for estimate:search an element with key in unordered_map is O(n) and add an element into an unordered_map is also O(n)
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID> & affiliations);

    // Estimate of performance:O(n)
    // Short rationale for estimate:traversal of an unordered_map is O(n)
    std::vector<PublicationID> all_publications();

    // Estimate of performance:O(1)
    // Short rationale for estimate:find an element with key in unordered_map is O(1)
    Name get_publication_name(PublicationID id);

    // Estimate of performance:O(1)
    // Short rationale for estimate:find an element with key in unordered_map is O(1)
    Year get_publication_year(PublicationID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate:search an element with key in unordered_map is O(n)
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate:search and element with key in unordered_map is O(n)
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance:O(n)
    // Short rationale for estimate:find an element with key in unordered_map is O(n)
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate:find an element with key in unordered_map and add an element to the end of a vector are all O(n)
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance:O(n)
    // Short rationale for estimate:traversal an unordered_map is O(n) and the big O of get_all_affiliations is also O(n)
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate:traversal an unordered_map is O(n)
    PublicationID get_parent(PublicationID id);

    // Estimate of performance:O(n*log(n))
    // Short rationale for estimate:remove_if for a vector is O(n) and sort for a vector is O(n*log(n)).So in general it is O(n*log(n))
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance:O(n)
    // Short rationale for estimate:find an element in unordered_map is O(n)
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);


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


private:

    // Add affiliation member to class
    std::unordered_map<AffiliationID, Affiliation> affiliations;
    std::vector<AffiliationID> sorted_names;
    // Add publication member to class
    std::unordered_map<PublicationID, Publication> publications;

    // Add reference relation to class
    std::unordered_map<PublicationID, std::vector<PublicationID>> references;
    bool sorted_state = false;

};

#endif // DATASTRUCTURES_HH
