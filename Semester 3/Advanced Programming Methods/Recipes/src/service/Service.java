package service;

import domain.Recipe;
import repository.Repository;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class Service {
    private Repository repo;

    public Service(Repository repo) {
        this.repo = repo;
    }

    public List<Recipe> getAllRecipes() {
        return repo.getAllRecipes().stream().sorted(Comparator.comparing(Recipe::getCuisine)).collect(Collectors.toList());
    }

    public List<Recipe> searchRecipes(String cuisine, String nameDescription) {
        return repo.getAllRecipes().stream()
                .filter(r-> r.getCuisine().equals(cuisine))
                .filter(r-> r.getName().contains(nameDescription) || r.getDescription().contains(nameDescription))
                .toList();
    }

    public void updateRecipe(String description, Recipe recipe) {
        repo.updateRecipe(description, recipe);
    }

    public List<Recipe> findRecipe(String ingredientsInput) {
        List<String> ingredients = List.of(ingredientsInput.split(","))
                .stream()
                .map(String::trim)
                .collect(Collectors.toList());

        return repo.getAllRecipes().stream()
                .filter(r -> {
                    List<String> recipeIngredients = List.of(r.getIngredients().split(","))
                            .stream()
                            .map(String::trim)
                            .collect(Collectors.toList());
                    return recipeIngredients.containsAll(ingredients);
                })
                .collect(Collectors.toList());
    }
}
