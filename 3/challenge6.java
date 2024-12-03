import java.nio.file.Files;
import java.nio.file.Path;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class challenge6 {
    public static void main(String[] args) {
        try {
            // File input = new File("input3.txt");
            int total = 0;
            String input = Files.readString(Path.of("input3.txt"));
            Pattern p = Pattern.compile("mul\\([0-9]+,[0-9]+\\)|don\\'t\\(\\)|do\\(\\)");
            Matcher m = p.matcher(input);
            Pattern p2 = Pattern.compile("[0-9]+");
            boolean check = true;
            while (m.find()) {
                if (m.group().equals("don't()")) {
                    check = false;
                    continue;
                } else if (m.group().equals("do()")) {
                    check = true;
                }

                if (!check) {
                    continue;
                }

                Matcher m2 = p2.matcher(m.group());
                int i = 0;
                int j = 0;
                if (m2.find()) {
                    i = Integer.parseInt(m2.group());
                }

                if (m2.find()) {
                    j = Integer.parseInt(m2.group());
                }

                total += i*j;
            }

            System.out.println(total);
        } catch (Exception e) {
        }

    }
}