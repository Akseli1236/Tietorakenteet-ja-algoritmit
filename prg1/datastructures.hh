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
#include <map>

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
    struct PubData{
        std::vector<AffiliationID> affId;
        Name pubName;
        Year pubYear;
        PublicationID pubId;
        PubData* parent;
        std::vector<PubData*> children = {};
    };

    struct Data {
        Name name;
        Coord coords;
        AffiliationID affId;
        std::vector<PubData*> pub = {};
        std::vector<PublicationID> pubs = {};

    };



    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate:
    // Getting the size of conainer is constant.
    unsigned int get_affiliation_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Clearing
    // containers is linear to the size of n and that
    // multiple times in n
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: function call
    // performs loop n times
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: adding elements to
    // map is log(n)
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // Find from undorder_map is constant on average
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // Find from undorder_map is constant on average
    Coord get_affiliation_coord(AffiliationID id);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // We loop trough n items;
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance: O(n^2)
    // Short rationale for estimate:
    // We need to loop trough 2 times n
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // We loop trough n items and get value from map
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // We loop trough n items
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // We loop trough n items
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID> & affiliations);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // We loop trough n items
    std::vector<PublicationID> all_publications();

    // Estimate of performance: O(1)
    // Short rationale for estimate:
    // Get value from unorderet_map
    Name get_publication_name(PublicationID id);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate:
    // Get value from map
    Year get_publication_year(PublicationID id);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate:
    // find from map is log(n)
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate:
    // Adding pairs to map is log(n)
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // We loop trough n item
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // operator[] in undoreder_map is constant, but worst case linear
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // We loop trough n items;
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate:
    // Find from unordered_map is constant
    PublicationID get_parent(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // We loop trough n items
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // recursively to the depth of n
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);


    // Non-compulsory operations

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate:
    // We loop tough n times and recursively call children
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    // Estimate of performance: O(1)
    // Short rationale for estimate:
    // remove with key is constant
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    PublicationID get_closest_common_parent(PublicationID id1, PublicationID id2);

    // Estimate of performance: O(1)
    // Short rationale for estimate:
    //remove with key is constant
    bool remove_publication(PublicationID publicationid);


private:
    std::unordered_map<AffiliationID, Data> aff;
    std::map<double,std::vector<Data>> affdist;
    std::map<Name,Data> affName;
    std::unordered_map<PublicationID, PubData> pub;
    std::unordered_map<double,std::vector<Data>> test;
    bool sorted_distance;
    bool sorted_name;
    std::vector<AffiliationID> orderedNames;
    std::vector<AffiliationID> orderedDistance;

};

#endif // DATASTRUCTURES_HH
