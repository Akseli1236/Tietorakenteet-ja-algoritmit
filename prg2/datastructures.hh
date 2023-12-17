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
#include <map>
#include <bits/stdc++.h>

// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
struct Connection;
// Type for a distance (in arbitrary units)
using Distance = int;

using Path = std::vector<Connection>;
using PathWithDist = std::vector<std::pair<Connection,Distance>>;

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

struct Connection
{
    AffiliationID aff1 = NO_AFFILIATION;
    AffiliationID aff2 = NO_AFFILIATION;
    Weight weight = NO_WEIGHT;
    bool operator==(const Connection& c1) const{
        return (aff1==c1.aff1) && (aff2==c1.aff2) && (weight==c1.weight);
    }
};
const Connection NO_CONNECTION{NO_AFFILIATION,NO_AFFILIATION,NO_WEIGHT};

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;
    }
};

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
class Graph {
public:
    Graph();
    void addEdge(const std::string& v, const std::string& w);
    void printGraph();

private:
    std::unordered_map<std::string, std::vector<std::string>> adjList;
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
    // Find from undorder_map is constant on average but in worst case O(n)
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // Find from undorder_map is constant on average but in worst case O(n)
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

    // PRG 2 functions:

    // Estimate of performance:O(n^2)
    // Short rationale for estimate:Used nested loops
    std::vector<Connection> get_connected_affiliations(AffiliationID id);

    // Estimate of performance:O(n^3)
    // Short rationale for estimate:We loop trough n times and call
    // O(n^2) function n times.
    std::vector<Connection> get_all_connections();

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: Calling function with
    // time complexity of O(n^2)
    Path get_any_path(AffiliationID source, AffiliationID target);

    // PRG2 optional functions

    // Estimate of performance:
    // Short rationale for estimate:
    Path get_path_with_least_affiliations(AffiliationID source, AffiliationID target);

    // Estimate of performance:
    // Short rationale for estimate:
    Path get_path_of_least_friction(AffiliationID source, AffiliationID target);

    // Estimate of performance:
    // Short rationale for estimate:
    PathWithDist get_shortest_path(AffiliationID source, AffiliationID target);


private:
    std::unordered_map<AffiliationID, Data> aff;
    //std::map<double,std::vector<Data>> affdist;
    std::map<Name,Data> affName;
    std::unordered_map<PublicationID, PubData> pub;
    std::unordered_map<double,std::vector<Data>> affDist;
    bool sorted_distance;
    bool sorted_name;
    std::vector<AffiliationID> orderedNames;
    std::vector<AffiliationID> orderedDistance;


    std::vector<AffiliationID> vis;


    std::unordered_map<AffiliationID, std::vector<Connection>> affConns;
    std::vector<Connection> allConnections;
    std::unordered_map<std::pair<AffiliationID, AffiliationID>, Path,pair_hash> conn;
    std::unordered_map<std::pair<AffiliationID, AffiliationID>, PathWithDist,pair_hash> shortestPath;

};

#endif // DATASTRUCTURES_HH
