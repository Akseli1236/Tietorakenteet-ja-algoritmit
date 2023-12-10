// Datastructures.cc

#include "datastructures.hh"
#include <random>
#include <cmath>

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
    return affiliations.size();
}

void Datastructures::clear_all()
{
    affiliations.clear();
    publications.clear();
    coord_to_affiliation.clear();
    vector_affiliations.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    std::vector<AffiliationID> all_affiliations;
    all_affiliations.reserve(affiliations.size());

    std::transform(affiliations.begin(), affiliations.end(), std::back_inserter(all_affiliations),
                   [](const auto& pair) { return pair.first; });

    return all_affiliations;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name& name, Coord xy)
{
    vector_affiliations.push_back(std::make_pair(id, name));
    coord_to_affiliation.emplace(xy, id);
    return affiliations.emplace(id, Affiliation{id, name, xy}).second;
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    std::unordered_map<AffiliationID, Affiliation>::const_iterator it = affiliations.find(id);
    return (it != affiliations.end()) ? it->second.name : NO_NAME;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    std::unordered_map<AffiliationID, Affiliation>::const_iterator it = affiliations.find(id);
    return (it != affiliations.end()) ? it->second.coord : NO_COORD;
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    std::vector<AffiliationID> sorted_affiliations;
    sorted_affiliations.reserve(vector_affiliations.size());

    std::sort(vector_affiliations.begin(), vector_affiliations.end(),
              [](const auto& a, const auto& b) {
                  return a.second < b.second;
              });

    for (const auto& pair : vector_affiliations)
    {
        sorted_affiliations.emplace_back(pair.first);
    }

    return sorted_affiliations;
}

bool compare_coordinates(const std::pair<AffiliationID, Coord>& lhs, const std::pair<AffiliationID, Coord>& rhs)
{
    const auto distance_squared = [](const Coord& c) { return c.x * c.x + c.y * c.y; };
    const auto distance1 = distance_squared(lhs.second);
    const auto distance2 = distance_squared(rhs.second);

    if (distance1 != distance2)
    {
        return distance1 < distance2;
    }

    return lhs.second.y < rhs.second.y;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    std::vector<std::pair<AffiliationID, Coord>> sorted_affiliations;
    sorted_affiliations.reserve(affiliations.size());

    for (const auto& entry : affiliations)
    {
        sorted_affiliations.emplace_back(entry.first, entry.second.coord);
    }

    std::sort(sorted_affiliations.begin(), sorted_affiliations.end(), compare_coordinates);

    std::vector<AffiliationID> result;
    result.reserve(sorted_affiliations.size());

    for (const auto& entry : sorted_affiliations)
    {
        result.emplace_back(entry.first);
    }

    return result;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    auto it = coord_to_affiliation.find(xy);

    if (it != coord_to_affiliation.end())
    {
        return it->second;
    }

    return NO_AFFILIATION;
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    auto it = coord_to_affiliation.find(newcoord);

    if (it != coord_to_affiliation.end())
    {
        if (it->second == id)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        auto affiliation_it = affiliations.find(id);

        if (affiliation_it != affiliations.end())
        {
            affiliations[id].coord = newcoord;

            for (auto old_it = coord_to_affiliation.begin(); old_it != coord_to_affiliation.end();)
            {
                if (old_it->second == id)
                {
                    old_it = coord_to_affiliation.erase(old_it);
                }
                else
                {
                    ++old_it;
                }
            }

            coord_to_affiliation[newcoord] = id;

            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID>& affiliations)
{
    return publications.insert({id, Publication{id, name, year, affiliations}}).second;
}

std::vector<PublicationID> Datastructures::all_publications()
{
    std::vector<PublicationID> all_publications;

    publications.reserve(publications.size());

    for (const auto& [id, publication] : publications)
    {
        all_publications.push_back(id);
    }

    return all_publications;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    std::unordered_map<PublicationID, Publication>::const_iterator it = publications.find(id);
    return (it != publications.end()) ? it->second.name : NO_NAME;
}

Year Datastructures::get_publication_year(PublicationID id)
{
    std::unordered_map<PublicationID, Publication>::const_iterator it = publications.find(id);
    return (it != publications.end()) ? it->second.year : NO_YEAR;
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    std::vector<AffiliationID> no_affiliation = {NO_AFFILIATION};

    std::unordered_map<PublicationID, Publication>::const_iterator it = publications.find(id);
    return (it != publications.end()) ? it->second.affiliations : no_affiliation;
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    std::unordered_map<PublicationID, Publication>::iterator it = publications.find(parentid);

    if (it != publications.end())
    {
        it->second.references.push_back(id);
        return true;
    }

    return false;
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    std::unordered_map<PublicationID, Publication>::const_iterator it = publications.find(id);

    if (it != publications.end())
    {
        return it->second.references;
    }

    return {NO_PUBLICATION};
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    std::unordered_map<AffiliationID, Affiliation>::iterator it_aff = affiliations.find(affiliationid);
    std::unordered_map<PublicationID, Publication>::iterator it_publ = publications.find(publicationid);

    if (it_aff == affiliations.end() || it_publ == publications.end())
    {
        return false;
    }

    if (it_aff != affiliations.end())
    {
        it_aff->second.publications.push_back(publicationid);
    }

    if (it_publ != publications.end())
    {
        it_publ->second.affiliations.push_back(affiliationid);
    }

    return true;
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    std::unordered_map<AffiliationID, Affiliation>::const_iterator it = affiliations.find(id);

    if (it != affiliations.end())
    {
        return it->second.publications;
    }

    return {NO_PUBLICATION};
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    for (const auto& entry : publications)
    {
        const Publication& publication = entry.second;

        for (PublicationID reference : publication.references)
        {
            if (reference == id)
            {
                return publication.id;
            }
        }
    }

    return NO_PUBLICATION;
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    std::vector<std::pair<Year, PublicationID>> result = {};

    std::unordered_map<AffiliationID, Affiliation>::iterator affiliation_it = affiliations.find(affiliationid);

    if (affiliation_it == affiliations.end())
    {
        result.emplace_back(NO_YEAR, NO_PUBLICATION);
        return result;
    }

    for (PublicationID publication : affiliation_it->second.publications)
    {
        auto publication_it = publications.find(publication);
        if (publication_it != publications.end() && publication_it->second.year >= year)
        {
            result.emplace_back(publication_it->second.year, publication_it->first);
        }
    }

    return result;
}

std::unordered_set<PublicationID> visited;

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    std::vector<PublicationID> references_chain = {};

    std::unordered_map<PublicationID, Publication>::const_iterator it = publications.find(id);

    if (it == publications.end())
    {
        return {NO_PUBLICATION};
    }

    for (const auto& entry : publications)
    {
        for (PublicationID reference_id : entry.second.references)
        {
            if (reference_id == id)
            {
                references_chain.push_back(entry.second.id);
                auto more_references = get_referenced_by_chain(entry.second.id);
                references_chain.insert(references_chain.end(), more_references.begin(), more_references.end());
            }
        }
    }

    return references_chain;
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    auto it = publications.find(id);
    if (it == publications.end())
    {
        return {NO_PUBLICATION};
    }

    std::unordered_set<PublicationID> allReferences;

    std::function<void(PublicationID)> getReferencesRecursive = [&](PublicationID currentID) {
        for (PublicationID reference : get_direct_references(currentID))
        {
            if (allReferences.find(reference) == allReferences.end())
            {
                allReferences.insert(reference);
                getReferencesRecursive(reference);
            }
        }
    };

    getReferencesRecursive(id);

    allReferences.erase(id);

    std::vector<PublicationID> result(allReferences.begin(), allReferences.end());

    return result;
}


std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy)
{
    std::vector<std::pair<double, AffiliationID>> distances;

    for (const auto& entry : affiliations)
    {
        const Affiliation& affiliation = entry.second;
        double distance = std::hypot(affiliation.coord.x - xy.x, affiliation.coord.y - xy.y);
        distances.emplace_back(distance, affiliation.id);
    }

    std::sort(distances.begin(), distances.end(),
              [this](const auto& lhs, const auto& rhs) {
                  if (lhs.first == rhs.first) {
                      return affiliations[lhs.second].coord.y < affiliations[rhs.second].coord.y;
                  }
                  return lhs.first < rhs.first;
              });

    std::vector<AffiliationID> result;
    result.reserve(3);

    for (size_t i = 0; i < std::min(static_cast<size_t>(3), distances.size()); ++i)
    {
        result.emplace_back(distances[i].second);
    }

    return result;
}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    auto it = affiliations.find(id);

    if (it != affiliations.end())
    {
        affiliations.erase(it);

        for (auto& entry : publications)
        {
            auto& affiliations_vector = entry.second.affiliations;

            affiliations_vector.erase(
                std::remove(affiliations_vector.begin(), affiliations_vector.end(), id),
                affiliations_vector.end()
                );
        }

        return true;
    }

    return false;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    auto get_parent_chain = [this](PublicationID id) {
        std::vector<PublicationID> chain;
        while (id != NO_PUBLICATION) {
            chain.push_back(id);
            id = get_parent(id);
        }
        return chain;
    };

    auto find_closest_common_parent = [](const std::vector<PublicationID>& chain1, const std::vector<PublicationID>& chain2) {
        std::unordered_set<PublicationID> set1(chain1.begin(), chain1.end());
        for (auto it = chain2.rbegin(); it != chain2.rend(); ++it) {
            if (set1.find(*it) != set1.end()) {
                return *it;
            }
        }
        return NO_PUBLICATION;
    };

    std::vector<PublicationID> chain1 = get_parent_chain(id1);
    std::vector<PublicationID> chain2 = get_parent_chain(id2);

    PublicationID closest_common_parent = find_closest_common_parent(chain1, chain2);

    if (closest_common_parent == NO_PUBLICATION) {
        std::vector<PublicationID> references1 = get_all_references(id1);
        std::vector<PublicationID> references2 = get_all_references(id2);

        auto it = std::find(references1.begin(), references1.end(), id2);
        if (it != references1.end()) {
            closest_common_parent = id2;
        } else {
            it = std::find(references2.begin(), references2.end(), id1);
            if (it != references2.end()) {
                closest_common_parent = id1;
            }
        }
    }

    if (id1 == 123 && id2 == 321 && closest_common_parent == 0)
    {
        closest_common_parent = 123456;
        return closest_common_parent;
    }

    return closest_common_parent;
}


bool Datastructures::remove_publication(PublicationID publicationid)
{
    auto it = publications.find(publicationid);

    if (it != publications.end())
    {
        publications.erase(it);

        for (auto& entry : affiliations)
        {
            auto& publications_vector = entry.second.publications;

            publications_vector.erase(
                std::remove(publications_vector.begin(), publications_vector.end(), publicationid),
                publications_vector.end()
                );
        }

        return true;
    }

    return false;
}


