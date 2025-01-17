package service;

import domain.Itinerary;
import repository.Repository;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class Service {
    private Repository repo;

    public Service(Repository repo) {
        this.repo = repo;
    }

    public List<Itinerary> getAllItineraries() {
        return  repo.getAllItineraries().stream().sorted(Comparator.comparing(Itinerary::getContinent)).collect(Collectors.toList());
    }

    public List<Itinerary> searchItineraries(String continent, String nameDescription) {
        return repo.getAllItineraries().stream()
                .filter(a-> a.getContinent().equals(continent))
                .filter(a-> a.getName().contains(nameDescription) || a.getPlacesToVisit().contains(nameDescription))
                .toList();
    }

    public void updateItinerary(String description, Itinerary Itinerary) {
        repo.updateItinerary(description, Itinerary);
    }

    public List<Itinerary> findItinerary(String placesInput) {
        List<String> places = List.of(placesInput.split(","))
                .stream()
                .map(String::trim)
                .collect(Collectors.toList());

        return repo.getAllItineraries().stream()
                .filter(a -> {
                    List<String> ItineraryPlaces = List.of(a.getPlacesToVisit().split(","))
                            .stream()
                            .map(String::trim)
                            .collect(Collectors.toList());
                    return ItineraryPlaces.containsAll(places);
                })
                .collect(Collectors.toList());
    }
}
