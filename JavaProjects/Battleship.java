package JavaProjects;

import java.util.Scanner; // you must import Scanner to use it

public class Battleship {
    private static String[][] playerBoard = { { " ", " ", " 0 ", " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", "\n" },
            { "0|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|0", "\n" },
            { "1|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|1", "\n" },
            { "2|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|2", "\n" },
            { "3|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|3", "\n" },
            { "4|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|4", "\n" },
            { "5|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|5", "\n" },
            { "6|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|6", "\n" },
            { " ", " ", " 0 ", " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", "\n" } };
    private static String[][] enemyBoard = { { " ", " ", " 0 ", " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", "\n" },
            { "0|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|0", "\n" },
            { "1|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|1", "\n" },
            { "2|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|2", "\n" },
            { "3|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|3", "\n" },
            { "4|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|4", "\n" },
            { "5|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|5", "\n" },
            { "6|", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "|6", "\n" },
            { " ", " ", " 0 ", " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", "\n" } };
    private static int playerScore = 5;
    private static int computerScore = 5;
    private static boolean gameOver = false;
    private static int boardMax = 8;
    private static int boardMin = 0;
    private static Scanner input = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.print("\033[H\033[2J");
        System.out.flush();
        System.out.println("");

        System.out.println("Player's Board");
        playerBoard = createBoard(playerBoard);

        System.out.println(" - : Missed");
        System.out.println(" x : Hit Ship");
        playerBoard = placeShips(playerBoard, "player");
        enemyBoard = placeShips(enemyBoard, "computer");

        while (!gameOver) {
            System.out.print("\033[H\033[2J");
            System.out.flush();

            System.out.println(" - : Missed");
            System.out.println(" x : Hit Ship");
            System.out.println("Player Ships: " + playerScore + " Computer Ships: " + computerScore);

            System.out.println("Player's Board");
            createBoard(playerBoard);

            System.out.println("Computer's Board");
            createBoard(enemyBoard);

            shootShip(enemyBoard, "player");
            gameOver = whoWins(playerScore, computerScore);
            if (gameOver == true) {
                break;
            }
            shootShip(playerBoard, "computer");
            gameOver = whoWins(playerScore, computerScore);
            if (gameOver == true) {
                break;
            }
        }
    }

    public static boolean whoWins(int playerScore, int computerScore) {
        if (playerScore == 0) {
            System.out.println("-----------------");
            System.out.println("You wins");
        } else if (computerScore == 0) {
            System.out.println("-----------------");
            System.out.println("Computer win");
        }

        if (playerScore == 0 || computerScore == 0) {
            return true;
        }
        return false;
    }

    public static String[][] createBoard(String[][] board) {
        // System.out.print("\033[H\033[2J");
        // System.out.flush();

        for (int row = 0; row < board.length; row++) {
            for (int col = 0; col < board[row].length; col++) {

                if (board[row][col].equals("a")) {
                    System.out.print(" @ ");
                } else if (board[row][col].equals("b")) {
                    System.out.print("   ");
                } else {
                    System.out.print(board[row][col]);
                }
            }
        }

        return board;
    }

    public static String[][] placeShips(String[][] board, String character) {
        System.out.println(character + " ship's coordinates");
        if (character.equals("player")) {
            System.out.println("I AM PLAYER");
            for (int truth = 0; truth < 5; truth++) {
                System.out.print("Enter X coordinate for your ship: ");
                int x = input.nextInt() + 1;
                System.out.print("Enter Y coordinate for your ship: ");
                int y = input.nextInt() + 1;

                // int z = 0;
                if (x >= boardMax || y >= boardMax || x <= boardMin || y <= boardMin) {
                    System.out.println("that is not valid number!");
                    truth--;
                } else if (board[y][x].equals("a")) {
                    System.out.println("You already have a ship here.");
                    truth--;
                } else {
                    board[y][x] = "a";
                }
            }
            return board;
        }

        if (character.equals("computer")) {
            System.out.println("I AM COMPUTER");
            for (int computer = 0; computer < 5; computer++) {
                int xOne = (int) (Math.random() * boardMax) + 1;
                int yOne = (int) (Math.random() * boardMax) + 1;

                if (xOne >= boardMax || yOne >= boardMax || xOne <= boardMin || yOne <= boardMin) {
                    computer--;
                } else if (board[yOne][xOne].equals("b")) {
                    computer--;
                } else {
                    board[yOne][xOne] = "b";
                    // System.out.println("Ship Deployed");
                }
            }

            return board;
        }

        return board;
    }

    public static String[][] shootShip(String[][] board, String character) {
        for (int u = 0; u < 1; u++) {
            if (character.equals("player")) {
                System.out.println("Your turn");
                System.out.print("Enter X coordinate to shoot: ");
                int shotX = input.nextInt() + 1;
                System.out.print("Enter Y coordinate to shoot: ");
                int shotY = input.nextInt() + 1;

                if (shotX >= boardMax || shotY >= boardMax || shotX <= boardMin || shotY <= boardMin) {
                    System.out.println("that is not valid number!");
                    u--;
                } else if (board[shotY][shotX].equals(" - ") || board[shotY][shotX].equals(" x ")) {
                    System.out.println("Try again, You already shot here");
                    u--;
                } else {
                    if (board[shotY][shotX].equals("b")) {
                        board[shotY][shotX] = " x ";
                        computerScore += -1;
                    } else {
                        System.out.println("You missed");
                        board[shotY][shotX] = " - ";
                    }
                }
            }

            if (character.equals("computer")) {
                int computerX = (int) (Math.random() * 10) + 1;
                int computerY = (int) (Math.random() * 10) + 1;

                if (computerX >= boardMax || computerY >= boardMax || computerX <= boardMin || computerY <= boardMin) {
                    System.out.println("that is not valid number!");
                    u--;
                } else if (board[computerY][computerX].equals(" - ") || board[computerY][computerX].equals(" x ")) {
                    u--;
                } else {
                    if (board[computerY][computerX].equals("a")) {
                        System.out.println("Computer hit your ship here.");
                        board[computerY][computerX] = " x ";
                        playerScore += -1;
                    } else if (board[computerY][computerX].equals("b")) {
                        u--;
                    } else {
                        System.out.println("Computer missed");
                        board[computerY][computerX] = " - ";
                    }
                }
            }
        }

        return board;
    }
}