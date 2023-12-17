// Datastructures.cc
//
// Student name:
// Student email:
// Student number:

#include "datastructures.hh"

#include <random>

#include <cmath>
#include <set>
#include <iostream>
#include <functional>
#include <bits/stdc++.h>
#include <queue>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

void Graph::addEdge(const std::string& v, const std::string& w) {
    adjList[v].push_back(w);
    adjList[w].push_back(v);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::get_affiliation_count()
{
    return aff.size();
}

void Datastructures::clear_all()
{
    aff.clear();
    pub.clear();
    affName.clear();
    affDist.clear();
    orderedNames.clear();
    orderedDistance.clear();
    affConns.clear();
    conn.clear();
    allConnections.clear();
}
std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    // Replace the line below with your implementation
    std::vector<AffiliationID> affiliations;
    for (const auto& affi : aff){
        affiliations.push_back(affi.first);
    }
    return affiliations;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name &name, Coord xy)
{
    double dist = sqrt(pow(xy.x,2) + pow(xy.y,2));
    Data newData = {name, xy, id};
    aff[id] = newData;
    affName[name] = newData;
    affDist[dist].push_back(newData);
    // Replace the line below with your implementation
    sorted_distance = false;
    sorted_name = false;


    return true;
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    if (aff.find(id) != aff.end()){
        return aff[id].name;
    }
    return NO_NAME;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    if (aff.find(id) != aff.end()){

        return aff[id].coords;
    }
    return {};

}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{



    if (!sorted_name){
        std::vector<AffiliationID> alphabetically;
        alphabetically.reserve(affName.size());
        for (const auto& affiliation : affName){
            alphabetically.push_back(affiliation.second.affId);

        }
        sorted_name = true;
        orderedNames = alphabetically;
    }

    return orderedNames;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    std::vector<AffiliationID> distance;

    std::vector<double> sortedKeys;


    if (!sorted_distance){
        distance.reserve(affDist.size());
        sortedKeys.reserve(affDist.size());

        // Extract and sort the keys
        for (const auto& entry : affDist) {
            sortedKeys.push_back(entry.first);
        }

        std::sort(sortedKeys.begin(), sortedKeys.end());

        for (const auto& sort : sortedKeys){
            if (affDist[sort].size() == 1){
                distance.push_back(affDist[sort].at(0).affId);
            }else{
                for (const auto& loop : affDist[sort]){
                    distance.push_back(std::move(loop.affId));
                }
            }
        }
        orderedDistance = distance;
        sorted_distance = true;

    }




    return orderedDistance;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    double dist = sqrt(pow(xy.x,2) + pow(xy.y,2));
    if (affDist[dist].size() == 1){
        return affDist[dist].at(0).affId;
    }

    for (const auto& it : affDist[dist]){
        if (it.coords == xy){
            return it.affId;
        }
    }
    return NO_AFFILIATION;
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{

    int i = 0;
    if (aff.find(id) != aff.end()){
        auto oldCoord = aff[id].coords;
        double dist = sqrt(pow(oldCoord.x,2) + pow(oldCoord.y,2));

        aff[id].coords = newcoord;

        double newdist = sqrt(pow(newcoord.x,2) + pow(newcoord.y,2));
        auto it = affDist.find(dist);

        Data newData = {};
        for (const auto& data : it->second){
            if (data.coords == oldCoord){
                newData = data;
                newData.coords = newcoord;
                break;
            }
            i++;

        }
        it->second.erase(it->second.begin() + i);
        affDist[newdist].push_back(newData);
        sorted_distance = false;
        return true;
    }

    return false;

}

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID> &affiliations)
{
    affConns.clear();
    allConnections.clear();
    conn.clear();
    shortestPath.clear();
    leastAffs.clear();
    leastFric.clear();
    pub[id] = {affiliations, name, year, id, nullptr};
    for (const auto& affId : affiliations){
        aff[affId].pub.push_back(&pub[id]);
    }
    return true;
}

std::vector<PublicationID> Datastructures::all_publications()
{

    std::vector<PublicationID> allPubs = {};
    for (const auto& pubs : pub){
        allPubs.push_back(pubs.first);
    }
    return allPubs;

}

Name Datastructures::get_publication_name(PublicationID id)
{
    if (pub.find(id) == pub.end()){
        return NO_NAME;
    }
    return pub[id].pubName;

}

Year Datastructures::get_publication_year(PublicationID id)
{
    if (pub.find(id) == pub.end()){
        return NO_YEAR;
    }
    return pub[id].pubYear;


}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    if (pub.find(id) != pub.end()){
        return pub[id].affId;
    }
    return {};


}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    pub[id].parent = &pub[parentid];
    pub[parentid].children.push_back(&pub[id]);
    return true;
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    std::vector<PublicationID> references = {};
    for (const auto& pubChildren : pub[id].children){
        references.push_back(pubChildren->pubId);
    }
    return references;
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    shortestPath.clear();
    leastAffs.clear();
    leastFric.clear();
    if (aff.find(affiliationid) != aff.end()){
        pub[publicationid].affId.push_back(affiliationid);
        aff[affiliationid].pubs.push_back(publicationid);
        return true;
    }
    return false;


}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    std::vector<PublicationID> pubs;
    if (aff.find(id) == aff.end()) {
        return {NO_PUBLICATION};
    }
    std::vector<PublicationID> vectorPub = aff[id].pubs;
    for (const auto& aPub : vectorPub){
        pubs.push_back(aPub);

    }
    return pubs;
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    if (pub.find(id) != pub.end()){
        if (pub[id].parent != nullptr){
            return pub[id].parent->pubId;
        }
    }
    return NO_PUBLICATION;

}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    std::vector<std::pair<Year, PublicationID>> afterYear;
    auto pubs = aff[affiliationid].pubs;
    for (auto pubFromAff : pubs){
        if (pub[pubFromAff].pubYear >= year){
            afterYear.push_back({pub[pubFromAff].pubYear, pubFromAff});
        }
    }
    return afterYear;
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    std::vector<PublicationID> chain;
    if (pub.find(id) == pub.end()){
        chain.push_back(NO_PUBLICATION);
    }

    if (pub[id].parent != nullptr){
        chain.push_back(pub[id].parent->pubId);
        auto getParent = get_referenced_by_chain(pub[id].parent->pubId);
        chain.insert(chain.begin(), getParent.begin(), getParent.end());
    }
    std::reverse(chain.begin(), chain.end());
    return chain;
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    std::vector<PublicationID> references;
    if (pub.find(id) == pub.end()){
        return {NO_PUBLICATION};
    }

    for (const auto& pubChildren : pub[id].children){
        references.push_back(pubChildren->pubId);

        auto grandChild = get_all_references(pubChildren->pubId);
        references.insert(references.begin(), grandChild.begin(), grandChild.end());
    }
    return references;
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy)
{
    std::vector<std::pair<double, AffiliationID>> sortedKeys;
    std::vector<AffiliationID> IDs;

    for (const auto& entry : aff) {
        double distance = sqrt(pow(xy.x-entry.second.coords.x,2)+pow(xy.y-entry.second.coords.y,2));
        sortedKeys.push_back({distance, entry.first});

    }

    std::sort(sortedKeys.begin(), sortedKeys.end());
    sortedKeys.erase( unique( sortedKeys.begin(), sortedKeys.end() ), sortedKeys.end() );

    for (const auto& i : sortedKeys){

        if (IDs.size() != 3){
            IDs.push_back(i.second);
        }

    }
    return IDs;

}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    if (aff.find(id) == aff.end()){
        return false;
    }
    affName.erase(aff[id].name);
    auto it = std::find(orderedNames.begin(), orderedNames.end(), id);
    auto it2 = std::find(orderedDistance.begin(), orderedDistance.end(), id);
    if (it != orderedNames.end()) {
        // Erase the element
        orderedNames.erase(it);
    }

    if (it2 != orderedDistance.end()) {
        orderedDistance.erase(it2);
    }

    double dist = sqrt(pow(aff[id].coords.x,2) + pow(aff[id].coords.y,2));
    if (affDist[dist].size() == 1){
        affDist.erase(dist);
    }else{
        for (auto it = affDist[dist].begin(); it != affDist[dist].end(); it++){
            if (it->affId == id){
                affDist[dist].erase(it);
                break;
            }
        }

    }

    aff.erase(id);


    return true;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    if (pub.find(id1) == pub.end() || pub.find(id2) == pub.end()){
        return NO_PUBLICATION;
    }
    if (id1 == id2){
        return id1;
    }
    auto parent1 = pub[id1].parent;
    auto parent2 = pub[id2].parent;
    if (parent1 == parent2){
        return parent1->pubId;
    }
    if (parent1 != nullptr && parent2 != nullptr){
        return get_closest_common_parent(parent1->pubId, parent2->pubId);
    }else if (parent1 != nullptr && parent2 == nullptr){
        return get_closest_common_parent(parent1->pubId, id2);
    }else if (parent1 == nullptr && parent2 != nullptr){
        return get_closest_common_parent(id1, parent2->pubId);
    }

    return NO_PUBLICATION;
}

bool Datastructures::remove_publication(PublicationID publicationid)
{
    auto pubIt = pub.find(publicationid);
    if (pubIt == pub.end()) {
        return false;  // Publication not found
    }

    // Remove from parent's children
    if (pubIt->second.parent != nullptr) {
        auto& parentChildren = pubIt->second.parent->children;
        parentChildren.erase(std::remove(parentChildren.begin(), parentChildren.end(), &pubIt->second), parentChildren.end());
    }

    // Set parent to nullptr for each child
    for (auto& child : pubIt->second.children) {
        child->parent = nullptr;
    }

    // Erase from pub map
    pub.erase(pubIt);

    // Erase from each affiliation's pubs
    for (auto& [affiliationID, affiliation] : aff) {
        auto it = std::find(affiliation.pubs.begin(), affiliation.pubs.end(), publicationid);
        if (it != affiliation.pubs.end()) {
            affiliation.pubs.erase(it);
        }
    }
    return true;
}

std::vector<Connection> Datastructures::get_connected_affiliations(AffiliationID id)
{

    std::vector<Connection> connections = {};
    std::unordered_map<AffiliationID, Connection> connected;

    if (aff.empty()){
        return {};
    }
    auto it = aff.find(id);
    if (it == aff.end()) {
        return {};
    }

    auto it2 = affConns.find(id);
    if (it2 == affConns.end()){
        for (const auto& singlePub : pub) {
            const std::vector<AffiliationID>& affs = singlePub.second.affId;
            auto it = std::find(affs.begin(), affs.end(), id);

            if (it != affs.end()) {
                for (const auto& otherAff : affs) {
                    if (otherAff != id) {
                        auto& connection = connected[otherAff];
                        if (connection.weight == -1){
                            connection = {id, otherAff, connection.weight + 2};
                        }else{
                            connection = {id, otherAff, connection.weight + 1};
                        }
                    }
                }
            }
        }

        connections.reserve(connected.size());
        for (const auto& connection : connected) {
            connections.push_back(connection.second);
        }
        affConns[id] = connections;
    }



    return affConns[id];
}

std::vector<Connection> Datastructures::get_all_connections()
{
    std::pair<AffiliationID, AffiliationID> pair;
    std::unordered_map<std::pair<AffiliationID, AffiliationID>, Connection, pair_hash> conn;
    if (allConnections.empty()){
        for (auto& singleAff : aff){
            std::vector<Connection> connections = get_connected_affiliations(singleAff.first);
            for (auto& connection : connections){
                if (connection.aff1 < connection.aff2){
                    pair.first = connection.aff1;
                    pair.second = connection.aff2;
                }else{
                    pair.first = connection.aff2;
                    pair.second = connection.aff1;
                }
                if (conn.find(pair) == conn.end() && connection.aff1 == pair.first){
                    conn[pair] = connection;
                    allConnections.push_back(connection);
                }
            }
        }

    }



    return allConnections;
}
Path Datastructures::get_any_path(AffiliationID source, AffiliationID target)
{


    std::vector<Connection> path = {};
    std::unordered_set<AffiliationID> visitedSet;

    if (conn.find({source, target}) != conn.end()) {
        return conn[{source, target}];
    }

    std::function<void(AffiliationID)> dfs = [&](AffiliationID current) {
        visitedSet.insert(current);
        auto connections = get_connected_affiliations(current);

        for (auto& aff : connections) {
            if (visitedSet.find(aff.aff2) == visitedSet.end()) {
                path.push_back(aff);

                if (aff.aff2 == target) {
                    conn[{source, target}] = path;
                    return;
                }

                dfs(aff.aff2);
                if (!path.empty() && path.back().aff2 == target) {
                    return;
                }

                path.pop_back();
            }
        }
    };

    dfs(source);
    visitedSet.clear();

    return path;

}


Path Datastructures::get_path_with_least_affiliations(AffiliationID source, AffiliationID target)
{
    if (leastAffs[{source,target}].size() != 0){
        return leastAffs[{source,target}];
    }
    std::vector<Connection> shortestPath;
    std::queue<std::vector<Connection>> q;
    std::unordered_set<AffiliationID> visitedSet;

    q.push({}); // Tyhjä polku aloitussolmuun

    while (!q.empty()) {
        std::vector<Connection> currentPath = q.front();
        q.pop();

        AffiliationID current = (!currentPath.empty()) ? currentPath.back().aff2 : source;

        visitedSet.insert(current);
        auto connections = get_connected_affiliations(current);

        for (auto& aff : connections) {
            if (visitedSet.find(aff.aff2) == visitedSet.end()) {
                std::vector<Connection> newPath = currentPath;
                newPath.push_back(aff);

                if (aff.aff2 == target) {
                    if (shortestPath.empty() || newPath.size() < shortestPath.size()) {
                        shortestPath = newPath;
                    }
                } else {
                    q.push(newPath);
                }
            }
        }
    }

    visitedSet.clear();
    leastAffs[{source, target}] = shortestPath;
    return shortestPath;
}


Distance heuristic(const Coord& coordA, const Coord& coordB) {
    // Yksinkertainen euklidinen etäisyys heuristiikka
    return sqrt(pow((coordB.x - coordA.x), 2) + pow((coordB.y - coordA.y), 2));
}


Path Datastructures::get_path_of_least_friction(AffiliationID source, AffiliationID target)
{

    if (leastFric[{source,target}].size() != 0){
        return leastFric[{source,target}];
    }

    auto comparePaths = [target](const Path& a, const Path& b) {
        // Find the maximum weight in each path
        Weight minWeightA = 0, minWeightB = 0;

        for (const auto& edge : a) {
            if (minWeightA == 0){
                minWeightA = edge.weight;
            }else if (edge.weight < minWeightA){
                minWeightA = edge.weight;
            }
        }

        for (const auto& edge : b) {
            if (minWeightB == 0){
                minWeightB = edge.weight;
            }else if (edge.weight < minWeightB){
                minWeightB = edge.weight;
            }
        }

        // First, prioritize paths with a greater maximum weight
        if (minWeightB != minWeightA) {
            return minWeightB > minWeightA;
        }

        // If the maximum weights are equal, then prioritize the shorter path
        return a.size() > b.size();
    };

    std::priority_queue<Path, std::vector<Path>, decltype(comparePaths)> pq(comparePaths);
    std::unordered_set<AffiliationID> visitedSet;
    Path shortestPath2;

    // Alustetaan Dijkstran algoritmin alkutila
    pq.push({});

    while (!pq.empty()) {
        // Otetaan keosta solmu, jolla on lyhin etäisyys
        Path currentPath = pq.top();
        pq.pop();

        // Jos solmu on jo käsitelty, älä käsittele sitä uudelleen
        if (!currentPath.empty() && visitedSet.find(currentPath.back().aff2) != visitedSet.end()) {
            continue;
        }

        // Lisätään solmu käytyjen joukkoon
        if (!currentPath.empty()) {
            visitedSet.insert(currentPath.back().aff2);
        }

        // Jos ollaan saavuttu kohdesolmuun
        if (!currentPath.empty() && currentPath.back().aff2 == target) {
            shortestPath2 = currentPath;
            break;
        }

        // Käy läpi kaikki solmun naapurit
        AffiliationID current = (!currentPath.empty()) ? currentPath.back().aff2 : source;
        auto connections = get_connected_affiliations(current);
        for (auto& aff : connections) {
            AffiliationID neighbor = aff.aff2;

            // Jos naapuri ei ole vielä käyty, lisätään se prioriteettijonoon
            if (visitedSet.find(neighbor) == visitedSet.end()) {

                Path newPath = currentPath;
                newPath.push_back(aff);

                pq.push(newPath);
            }
        }
    }

    return shortestPath2;
}


PathWithDist Datastructures::get_shortest_path(AffiliationID source, AffiliationID target)
{


    if (shortestPath[{source, target}].size() != 0){
        return shortestPath[{source, target}];
    }


    // Alustetaan Dijkstran algoritmiin tarvittavat rakenteet
    auto comparePaths = [this, target](const PathWithDist& a, const PathWithDist& b) {
        if (a.empty() && b.empty()) {
            return false; // Jos molemmat polut ovat tyhjiä, ne ovat yhtä pitkiä (tai lyhyitä)
        }

        if (a.empty()) {
            return false; // Tyhjä polku on aina "lyhyempi" kuin ei-tyhjä polku
        }

        if (b.empty()) {
            return true; // Ei-tyhjä polku on aina "pidempi" kuin tyhjä polku
        }

        auto coordA = get_affiliation_coord(a.back().first.aff2);
        auto coordB = get_affiliation_coord(b.back().first.aff2);

        return (a.back().second + heuristic(coordA, get_affiliation_coord(target))) >
               (b.back().second + heuristic(coordB, get_affiliation_coord(target)));
    };

    std::priority_queue<PathWithDist, std::vector<PathWithDist>, decltype(comparePaths)> pq(comparePaths);
    std::unordered_set<AffiliationID> visitedSet;
    PathWithDist shortestPath2;

    // Alustetaan Dijkstran algoritmin alkutila
    pq.push({});

    while (!pq.empty()) {
        // Otetaan keosta solmu, jolla on lyhin etäisyys
        PathWithDist currentPath = pq.top();
        pq.pop();

        // Jos solmu on jo käsitelty, älä käsittele sitä uudelleen
        if (!currentPath.empty() && visitedSet.find(currentPath.back().first.aff2) != visitedSet.end()) {
            continue;
        }

        // Lisätään solmu käytyjen joukkoon
        if (!currentPath.empty()) {
            visitedSet.insert(currentPath.back().first.aff2);
        }

        // Jos ollaan saavuttu kohdesolmuun
        if (!currentPath.empty() && currentPath.back().first.aff2 == target) {
            shortestPath2 = currentPath;
            break;
        }

        // Käy läpi kaikki solmun naapurit
        AffiliationID current = (!currentPath.empty()) ? currentPath.back().first.aff2 : source;
        auto connections = get_connected_affiliations(current);
        for (auto& aff : connections) {
            AffiliationID neighbor = aff.aff2;

            // Jos naapuri ei ole vielä käyty, lisätään se prioriteettijonoon
            if (visitedSet.find(neighbor) == visitedSet.end()) {
                auto coord1 = get_affiliation_coord(aff.aff1);
                auto coord2 = get_affiliation_coord(aff.aff2);
                Distance edgeDist = sqrt(pow((coord2.x - coord1.x), 2) + pow((coord2.y - coord1.y), 2));

                PathWithDist newPath = currentPath;
                newPath.push_back({aff, edgeDist});

                pq.push(newPath);
            }
        }
    }

    // Tallenna laskettu lyhin polku
    shortestPath[{source, target}] = shortestPath2;

    return shortestPath2;

}


