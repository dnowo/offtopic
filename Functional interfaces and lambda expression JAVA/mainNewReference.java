import java.util.function.BiFunction;
import java.util.function.Consumer;
import java.util.function.Supplier;

public class mainNewReference {
    public static void main(String[] args) {
        BiFunction<Integer, String, Human> humanBiFunction = Human::new;
        Human humanRob = humanBiFunction.apply(12,"Rob");
        Consumer<String> humanConsumer = x->System.out.println(x); // Zamiennie z System.out::println;
        humanConsumer.accept(humanRob.toString());
    }

}
class Human{
    private int age;
    private String name;

    public Human(int age, String name) {
        this.age = age;
        this.name = name;
    }
    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    @Override
    public String toString() {
        return "Human{" +
                "age=" + age +
                ", name='" + name + '\'' +
                '}';
    }
}