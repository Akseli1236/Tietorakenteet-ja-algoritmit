// Datastructures.cc
//
// Student name: Akseli Ahonen
// Student email: akseli.ahonen@tuni.fi
// Student number: 150313812

#include "datastructures.hh"

#include <random>

#include <cmath>
#include <map>
#include <iostream>
#include <algorithm>
#include <iterator>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
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
    //affdist.clear();
    affName.clear();
    test.clear();
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
    //affdist[dist].push_back(newData);
    affName[name] = newData;
    test[dist].push_back(newData);
    // Replace the line below with your implementation
    sorted = false;


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


    std::vector<AffiliationID> alphabetically;
    alphabetically.reserve(affName.size());

    for (const auto& affiliation : affName){
        alphabetically.push_back(affiliation.second.affId);

    }
    return alphabetically;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    std::vector<AffiliationID> distance;
    distance.reserve(test.size());

    if (!sorted){


        std::vector<std::pair<double, std::vector<Data>>> sortedPairs(test.begin(), test.end());
        kek = sortedPairs;

        std::sort(kek.begin(), kek.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
        sorted = true;
    }


    for (const auto& sort : kek){
        if (sort.second.size() == 1){
            distance.push_back(sort.second.at(0).affId);
        }else{
            for (const auto& loop : sort.second){
                distance.push_back(std::move(loop.affId));
            }
        }
    }

/*
    for (const auto& singleAff : affdist) {
        //double dist = sqrt(pow(singleAff.second.coords.x,2) + pow(singleAff.second.coords.y,2));
        // Transform pairs from singleAff.second.distance to distance vector
        if (singleAff.second.size() == 1){
            distance.push_back(singleAff.second.at(0).affId);
        }else{
            for (const auto& loop : singleAff.second){
                distance.push_back(std::move(loop.affId));
            }
        }

    }
*/
    return distance;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    double dist = sqrt(pow(xy.x,2) + pow(xy.y,2));
    if (test[dist].size() == 1){
        std::cout << test[dist].at(0).name << std::endl;
        return test[dist].at(0).affId;
    }

    for (const auto& it : test[dist]){
        std::cout << it.name << it.coords.x << it.coords.y << std::endl;
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
        auto it = test.find(dist);

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
        test[newdist].push_back(newData);

        return true;
    }

    return false;
/*
    int i = 0;
    if (aff.find(id) != aff.end()){
        auto oldCoord = aff[id].coords;
        double dist = sqrt(pow(oldCoord.x,2) + pow(oldCoord.y,2));

        aff[id].coords = newcoord;

        double newdist = sqrt(pow(newcoord.x,2) + pow(newcoord.y,2));
        auto it = affdist.find(dist);

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
        affdist[newdist].push_back(newData);

        return true;
    }

    return false;
 */

}

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID> &affiliations)
{
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
    return pub[id].pubName;

}

Year Datastructures::get_publication_year(PublicationID id)
{
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
    if (aff.find(affiliationid) != aff.end()){
        pub[publicationid].affId.push_back(affiliationid);
        aff[affiliationid].pubs.push_back(publicationid);
        return true;
    }
    return false;


}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    std::vector<PublicationID> pubs = {};
    if (aff.find(id) == aff.end()) {
        return pubs;
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
    for (const auto& pubChildren : pub[id].children){
        references.push_back(pubChildren->pubId);

        auto grandChild = get_all_references(pubChildren->pubId);
        references.insert(references.begin(), grandChild.begin(), grandChild.end());

    }
    return references;
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord /*xy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_affiliations_closest_to()");
}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    aff.erase(id);
    return true;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID /*id1*/, PublicationID /*id2*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_closest_common_parent()");
}

bool Datastructures::remove_publication(PublicationID publicationid)
{
    pub.erase(publicationid);
    return true;
}


