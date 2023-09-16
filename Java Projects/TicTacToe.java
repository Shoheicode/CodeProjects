package CreateTaskForComputerScienceAP;

import java.util.Scanner;

public class TicTacToeCopy {
    public static Scanner userInput;
    public static String[][] playerBoard = {
        {"   ", "|", "   ", "|", "   ", "\n"},
        {"---", "-", "---", "-", "---", "\n"},
        {"   ", "|", "   ", "|", "   ", "\n"},
        {"---", "-", "---", "-", "---", "\n"},
        {"   ", "|", "   ", "|", "   ", "\n"}
    };

    public static String[][] playerInputsDisplay = 
    {
        {"TL", " | ", "TM", " | ", "TR", "\n"},
        {"----", "-", "---", "-", "----", "\n"},
        {"ML", " | ", "MM", " | ", "MR", "\n"},
        {"----", "-", "---", "-", "----", "\n"},
        {"BL", " | ", "BM", " | ", "BR", "\n"}
    };

    public static String[] boardInputs = {
        "TL", "TM", "TR",
        "ML", "MM", "MR",
        "BL", "BM", "BR"};

    public static String[] invalidInputs = {
        "", "", "", "", "", "","", "", "" };

    public static boolean gameOver = false;
    public static String playerInput = "";

    public static void main(String[] args) {
        System.out.flush();
        while(!gameOver){
            // System.out.print("\033[H\033[2J");
            // System.out.flush();

            createBoard(playerInputsDisplay);
            System.out.println();
            System.out.println("You are X");
            System.out.println("Computer is O");

            playerBoard = createBoard(playerBoard);
            playerBoard = placeX(playerBoard);
            gameOver = threeInARow(playerBoard);
            gameOver = isBoardFilled(playerBoard, gameOver);
            
            if(gameOver){
                break;
            }

            playerBoard = placeO(playerBoard);
            gameOver = threeInARow(playerBoard);

            if(gameOver){
                break;
            }
        }
        System.out.flush();
    }

    public static String[][] placeX(String[][] board){
        userInput = new Scanner(System.in);
        System.out.println("Your turn");
        boolean moveCorrect = false;
        String input = "";

        while(!moveCorrect){
            input = userInput.nextLine();
            for(int word = 0; word < boardInputs.length; word++){
                if(input.equals(boardInputs[word]) && invalidInputs[word].equals("")){
                    moveCorrect = true;
                    invalidInputs[word] = input;
                    break;
                    
                }
            }

            if(moveCorrect == false){
                System.out.println("Not a valid move. Please try again.");
            }
        }

        for(int row = 0; row < playerInputsDisplay.length; row++){
            for(int col = 0; col < playerInputsDisplay[row].length; col++){
                if(board[row][col].equals("   ") && input.equals(playerInputsDisplay[row][col])){
                    board[row][col] = " X ";
                }
            } 
        }

        return board;
    }

    public static String[][] placeO(String[][] board){
        System.out.println("COMPUTER MOVE");
        boolean moveCorrect = false;
        String input = "";

        while(!moveCorrect){
            input = checkIfTwoInARowX(board);
            input = checkIfTwoInARowO(board, input);
            if(input.equals("")){
                System.out.println("RANDOM MOVE");
                int randomMove = (int)(Math.random() * 9);
                input = boardInputs[randomMove];
            }

            for(int word = 0; word < boardInputs.length; word++){
                if(input.equals(boardInputs[word]) && invalidInputs[word].equals("")){
                    moveCorrect = true;
                    invalidInputs[word] = input;
                }
            }
        }

        for(int row = 0; row < playerInputsDisplay.length; row++){
            for(int col = 0; col < playerInputsDisplay[row].length; col++){
                if(board[row][col].equals("   ") && input.equals(playerInputsDisplay[row][col])){
                    board[row][col] = " O ";
                }
            } 
        }

        return board;
    }

    public static String checkIfTwoInARowX(String[][] board){
        String diagonalX = "";
        String horizontalX = "";
        String verticalX = "";
        
        diagonalX = checkTwoInARowDiagonalX(board);
        horizontalX = checkTwoInARowHorizontalX(board);
        verticalX = checkTwoInARowVerticalX(board);

        if(!verticalX.equals("")){
            return verticalX;
        }
        if(!horizontalX.equals("")){
            return horizontalX;
        }
        if(!diagonalX.equals("")){
            return diagonalX;
        }

        return "";
    }

    public static String checkTwoInARowHorizontalX(String[][] board){
        boolean isDone = true;
        for(int row = 0; row < board.length; row+=2){
            if((board[row][0].equals(" X ") && board[row][2].equals(" X "))){                    
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[row][4].equals(invalidInputs[index])){
                        isDone = false;
                    }
                }
                if(isDone){
                    return playerInputsDisplay[row][4];
                }
                isDone = true;
            }
            else if((board[row][2].equals(" X ") && board[row][4].equals(" X "))){
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[row][0].equals(invalidInputs[index])){
                        isDone = false;
                    }
                }
                if(isDone){
                    return playerInputsDisplay[row][0];
                }
                isDone = true;
            }
            else if((board[row][0].equals(" X ") && board[row][4].equals(" X "))){
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[row][2].equals(invalidInputs[index])){
                        isDone = false;
                    }
                }
                if(isDone){
                    return playerInputsDisplay[row][2];
                }
                isDone = true;
            }
        }

        return "";
    }

    public static String checkTwoInARowVerticalX(String[][] board){
        boolean isDone = true;
        for(int col = 0; col < board.length; col++){
            if((board[0][col].equals(" X ") && board[2][col].equals(" X "))){                    
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[4][col].equals(invalidInputs[index])){
                        isDone = false;
                    }
                }
                if(isDone){
                    return playerInputsDisplay[4][col];
                }
                isDone = true;
            }
            else if((board[2][col].equals(" X ") && board[4][col].equals(" X "))){
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[0][col].equals(invalidInputs[index])){
                        isDone =false;
                    }
                }
                if(isDone){
                    return playerInputsDisplay[0][col];
                }
                isDone = true;
            }
            else if((board[0][col].equals(" X ") && board[4][col].equals(" X "))){
                System.out.println("HFEEE");
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[2][col].equals(invalidInputs[index])){
                        isDone = false;
                    }
                }
                if(isDone){
                    System.out.println(playerInputsDisplay[2][col]);
                    return playerInputsDisplay[2][col];
                }
                isDone = true;
            }
        }
        return "";
    }

    public static String checkTwoInARowDiagonalX(String[][] board){
        boolean isDone = true;
        //Checking X Diagonal with position (0,0) and (4,4)

        if((board[0][0].equals(" X ") && board[2][2].equals(" X ") )){                    
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[4][4].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[4][4];
            }
            isDone = true;
        }

        //Checking X Diagonal with position (2,2) and (4,4)

        else if((board[2][2].equals(" X ") && board[4][4].equals(" X "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[0][0].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[0][0];
            }
            isDone = true;
        }

        //Checking X Diagonal with position (0,0) and (4,4)

        else if((board[0][0].equals(" X ") && board[4][4].equals(" X "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[2][2].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[2][2];
            }
            isDone = true;
        }

        if((board[0][4].equals(" X ") && board[2][2].equals(" X ") )){                    
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[4][0].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[4][0];
            }
            isDone = true;
        }
        
        else if((board[2][2].equals(" X ") && board[4][0].equals(" X "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[0][4].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[0][4];
            }
            isDone = true;
        }
        else if((board[0][4].equals(" X ") && board[4][0].equals(" X "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[2][2].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[2][2];
            }
            isDone = true;
        }

        return "";
    }

    public static String checkIfTwoInARowO(String[][] board, String input){
        String diagonalO = "";
        String horizontalO = "";
        String verticalO = "";

        diagonalO = checkTwoInARowDiagonalO(board);
        horizontalO = checkTwoInARowHorizontalO(board);
        verticalO = checkTwoInARowVerticalO(board);

        if(!verticalO.equals("")){
            return verticalO;
        }
        if(!horizontalO.equals("")){
            return horizontalO;
        }
        if(!diagonalO.equals("")){
            return diagonalO;
        }

        return input;
    }

    public static String checkTwoInARowHorizontalO(String[][] board){
        boolean isDone = true;
        for(int row = 0; row < board.length; row+=2){
            if((board[row][0].equals(" O ") && board[row][2].equals(" O "))){                    
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[row][4].equals(invalidInputs[index])){
                        isDone = false;
                    }
                }
                if(isDone){
                    return playerInputsDisplay[row][4];
                }
                isDone = true;
            }
            else if((board[row][2].equals(" O ") && board[row][4].equals(" O "))){
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[row][0].equals(invalidInputs[index])){
                        isDone = false;
                    }
                }
                if(isDone){
                    return playerInputsDisplay[row][0];
                }
                isDone = true;
            }
            else if((board[row][0].equals(" O ") && board[row][4].equals(" O "))){
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[row][2].equals(invalidInputs[index])){
                        isDone = false;
                    }
                }
                if(isDone){
                    return playerInputsDisplay[row][2];
                }
                isDone = true;
            }
        }

        return "";
    }

    public static String checkTwoInARowVerticalO(String[][] board){
        boolean isDone = true;
        for(int col = 0; col < board.length; col++){
            if((board[0][col].equals(" O ") && board[2][col].equals(" O "))){                    
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[4][col].equals(invalidInputs[index])){
                        isDone = false;
                    }
                }
                if(isDone){
                    return playerInputsDisplay[4][col];
                }
                isDone = true;
            }
            else if((board[2][col].equals(" O ") && board[4][col].equals(" O "))){
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[0][col].equals(invalidInputs[index])){
                        isDone =false;
                    }
                }
                if(isDone){
                    return playerInputsDisplay[0][col];
                }
                isDone = true;
            }
            else if((board[0][col].equals(" O ") && board[4][col].equals(" O "))){
                System.out.println("HFEEE");
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[2][col].equals(invalidInputs[index])){
                        isDone = false;
                    }
                }
                if(isDone){
                    System.out.println(playerInputsDisplay[2][col]);
                    return playerInputsDisplay[2][col];
                }
                isDone = true;
            }
        }
        return "";
    }

    public static String checkTwoInARowDiagonalO(String[][] board){
        boolean isDone = true;
        //Checking X Diagonal with position (0,0) and (4,4)

        if((board[0][0].equals(" O ") && board[2][2].equals(" O ") )){                    
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[4][4].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[4][4];
            }
            isDone = true;
        }

        //Checking X Diagonal with position (2,2) and (4,4)

        else if((board[2][2].equals(" O ") && board[4][4].equals(" O "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[0][0].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[0][0];
            }
            isDone = true;
        }

        //Checking X Diagonal with position (0,0) and (4,4)

        else if((board[0][0].equals(" O ") && board[4][4].equals(" O "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[2][2].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[2][2];
            }
            isDone = true;
        }

        if((board[0][4].equals(" O ") && board[2][2].equals(" O ") )){                    
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[4][0].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[4][0];
            }
            isDone = true;
        }
        
        else if((board[2][2].equals(" O ") && board[4][0].equals(" O "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[0][4].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[0][4];
            }
            isDone = true;
        }
        else if((board[0][4].equals(" O ") && board[4][0].equals(" O "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[2][2].equals(invalidInputs[index])){
                    isDone = false;
                }
            }
            if(isDone){
                return playerInputsDisplay[2][2];
            }
            isDone = true;
        }

        return "";
    }




    public static boolean twoInARowDiagonal(String[][] board){
        if(board[0][0].equals(" X ") || board[0][4].equals(" X ")){
            if(board[2][2].equals(" X ")){
                return true;
            }
        }
        else if(board[2][2].equals(" X ")){
            if(board[4][4].equals(" X ") && board[4][0].equals(" X ")){
                return true;
            }
        }
        if(board[0][0].equals(" O ") || board[0][4].equals(" O ")){
            if(board[2][2].equals(" O ")){
                return true;
            }
        }
        else if(board[2][2].equals(" O ")){
            if(board[4][4].equals(" O ") || board[4][0].equals(" O ")){
                return true;
            }
        }
        if(board[0][0].equals(" X ")){
            if(board[4][4].equals(" X ")){
                return true;
            }
        }
        else if(board[0][0].equals(" O ")){
            if(board[4][4].equals(" O ")){
                return true;
            }
        }
        if(board[0][4].equals(" X ")){
            if(board[4][0].equals(" X ")){
                return true;
            }
        }
        else if(board[0][4].equals(" O ")){
            if(board[4][0].equals(" O ")){
                return true;
            }
        }

        return false;
    }

    public static String checkTwoInARowDiagonal(String[][] board){
        //Downward Sloping

        System.out.println("DIAGONAL");
        
        //Checking O Diagonal with position (0,0) and (2,2)

        if((board[0][0].equals(" O ") && board[2][2].equals(" O "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[4][4].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
            return playerInputsDisplay[4][4];
        }

        //Checking O Diagonal with position (2,2) and (4,4)
        
        else if((board[2][2].equals(" O ") && board[4][4].equals(" O "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[0][0].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
                return playerInputsDisplay[0][0];
        }

        //Chekcing O diagonal with position (0,0) and (4,4)

        else if((board[0][0].equals(" O ") && board[4][4].equals(" O "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[2][2].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
                return playerInputsDisplay[2][2];
        }

        //Checking X Diagonal with position (0,0) and (4,4)

        else if((board[0][0].equals(" X ") && board[2][2].equals(" X ") )){                    
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[4][4].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
            return playerInputsDisplay[4][4];
        }

        //Checking X Diagonal with position (2,2) and (4,4)

        else if((board[2][2].equals(" X ") && board[4][4].equals(" X "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[0][0].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
                return playerInputsDisplay[0][0];
        }

        //Checking X Diagonal with position (0,0) and (4,4)

        else if((board[0][0].equals(" X ") && board[4][4].equals(" X "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[2][2].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
                return playerInputsDisplay[2][2];
        }

        //Upward Sloping
        
        if ((board[0][4].equals(" O ") && board[2][2].equals(" O "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[4][0].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
            return playerInputsDisplay[4][0];
        }

        else if((board[2][2].equals(" O ") && board[4][0].equals(" O "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[0][4].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
            return playerInputsDisplay[0][4];
        }

        else if((board[0][4].equals(" O ") && board[4][0].equals(" O "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[2][2].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
            return playerInputsDisplay[2][2];
        }

        else if((board[0][4].equals(" X ") && board[2][2].equals(" X ") )){                    
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[4][0].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
            return playerInputsDisplay[4][0];
        }
        else if((board[2][2].equals(" X ") && board[4][0].equals(" X "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[0][4].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
            return playerInputsDisplay[0][4];
        }
        else if((board[0][4].equals(" X ") && board[4][0].equals(" X "))){
            for(int index = 0; index < boardInputs.length; index++){
                if(playerInputsDisplay[2][2].equals(invalidInputs[index])){
                    int randomMove = (int)(Math.random() * 9);
                    return boardInputs[randomMove];
                }
            }
            return playerInputsDisplay[2][2];
        }

        return "";
    }

    public static boolean twoInARowHorizontal(String[][] board){
        for(int row = 0; row < board.length; row++){
            if(board[row][0].equals(" X ")){
                if(board[row][2].equals(" X ")){
                    return true;
                }
            }
            else if(board[row][2].equals(" X ")){
                if(board[row][4].equals(" X ")){
                    return true;
                }
            }
            if(board[row][0].equals(" O ")){
                if(board[row][2].equals(" O ")){
                    return true;
                }
            }
            else if(board[row][2].equals(" O ")){
                if(board[row][4].equals(" O ")){
                    return true;
                }
            }
            if(board[row][0].equals(" X ")){
                if(board[row][4].equals(" X ")){
                    return true;
                }
            }
            else if(board[row][0].equals(" O ")){
                if(board[row][4].equals(" O ")){
                    return true;
                }
            }
        }

        return false;
    }

    public static String checkTwoInARowHoriztonal(String[][] board){
        System.out.println("HORIZONTAL");
        for(int row = 0; row < board.length; row++){
            if((board[row][0].equals(" X ") && board[row][2].equals(" X ") ) || (board[row][0].equals(" O ") && board[row][2].equals(" O "))){                    
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[row][4].equals(invalidInputs[index])){
                        int randomMove = (int)(Math.random() * 9);
                        return boardInputs[randomMove];
                    }
                }
                return playerInputsDisplay[row][4];
            }
            else if((board[row][2].equals(" X ") && board[row][4].equals(" X ")) || (board[row][2].equals(" O ") && board[row][4].equals(" O "))){
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[row][0].equals(invalidInputs[index])){
                        int randomMove = (int)(Math.random() * 9);
                        return boardInputs[randomMove];
                    }
                }
                    return playerInputsDisplay[row][0];
            }
            else if((board[row][0].equals(" X ") && board[row][4].equals(" X ")) || (board[row][0].equals(" O ") && board[row][4].equals(" O "))){
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[row][2].equals(invalidInputs[index])){
                        int randomMove = (int)(Math.random() * 9);
                        return boardInputs[randomMove];
                    }
                }
                    return playerInputsDisplay[row][2];
            }
        }

        return "";
    }

    public static boolean twoInARowVertical(String[][] board){
        for(int col = 0; col < board.length; col++){
            if(board[0][col].equals(" X ")){
                if(board[2][col].equals(" X ")){
                    return true;
                }
            }
            else if(board[2][col].equals(" X ")){
                if(board[4][col].equals(" X ")){
                    return true;
                }
            }
            if(board[0][col].equals(" O ")){
                if(board[2][col].equals(" O ")){
                    return true;
                }
            }
            else if(board[2][col].equals(" O ")){
                if(board[4][col].equals(" O ")){
                    return true;
                }
            }
            if(board[0][col].equals(" X ")){
                if(board[4][col].equals(" X ")){
                    return true;
                }
            }
            else if(board[0][col].equals(" O ")){
                if(board[4][col].equals(" O ")){
                    return true;
                }
            }
        }

        return false;
    }



    public static String checkTwoInARowVertical(String[][] board){
        System.out.println("VERTICAL");
        for(int col = 0; col < board.length; col++){
            if ((board[0][col].equals(" O ") && board[2][col].equals(" O "))){
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[4][col].equals(invalidInputs[index])){
                        int randomMove = (int)(Math.random() * 9);
                        return boardInputs[randomMove];
                    }
                }
                return playerInputsDisplay[4][col];
            }
            else if((board[2][col].equals(" O ") && board[4][col].equals(" O "))){
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[0][col].equals(invalidInputs[index])){
                        int randomMove = (int)(Math.random() * 9);
                        return boardInputs[randomMove];
                    }
                }
                    return playerInputsDisplay[0][col];
            }
            else if( (board[0][col].equals(" O ") && board[4][col].equals(" O "))){
                System.out.println("HFEEE");
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[2][col].equals(invalidInputs[index])){
                        int randomMove = (int)(Math.random() * 9);
                        System.out.println(boardInputs[randomMove]);
                        return boardInputs[randomMove];
                    }
                }
                System.out.println("HIIIII");
                return playerInputsDisplay[2][col];
            }
        }
        for(int col = 0; col < board.length; col++){
            if((board[0][col].equals(" X ") && board[2][col].equals(" X "))){                    
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[4][col].equals(invalidInputs[index])){
                        int randomMove = (int)(Math.random() * 9);
                        return boardInputs[randomMove];
                    }
                }
                return playerInputsDisplay[4][col];
            }
            else if((board[2][col].equals(" X ") && board[4][col].equals(" X "))){
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[0][col].equals(invalidInputs[index])){
                        int randomMove = (int)(Math.random() * 9);
                        return boardInputs[randomMove];
                    }
                }
                return playerInputsDisplay[0][col];
            }
            else if((board[0][col].equals(" X ") && board[4][col].equals(" X "))){
                System.out.println("HFEEE");
                for(int index = 0; index < invalidInputs.length; index++){
                    if(playerInputsDisplay[2][col].equals(invalidInputs[index])){
                        int randomMove = (int)(Math.random() * 9);
                        System.out.println("HIIIII");
                        return boardInputs[randomMove];
                    }
                }
                System.out.println(playerInputsDisplay[2][col]);
                return playerInputsDisplay[2][col];
            }
        }

        return "";
    }



    public static boolean threeInARow(String[][] board){
        boolean inARow = false;
        if(threeInARowVertical(board) || threeInARowHorizontal(board) || threeInARowDiagonal(board)){
            return true;
        } 

        return inARow;
    }

    public static boolean threeInARowVertical(String[][] board){
        for(int col = 0; col < board.length; col++){
            if(board[0][col].equals(" X ")){
                if(board[2][col].equals(" X ") && board[4][col].equals(" X ")){
                    System.out.print("\033[H\033[2J");
                    System.out.flush();
                    System.out.println("Player Wins");
                    userInput.close();
                    createBoard(board);
                    return true;
                }
            }
            else if (board[0][col].equals(" O ")){
                if(board[2][col].equals(" O ") && board[4][col].equals(" O ")){
                    System.out.print("\033[H\033[2J");
                    System.out.flush();
                    System.out.println("Computer Wins");
                    userInput.close();
                    createBoard(board);
                    return true;
                }
            }
        }

        return false;
    }

    public static boolean threeInARowHorizontal(String[][] board){
        for(int row = 0; row < board.length; row++){
            if(board[row][0].equals(" X ")){
                if(board[row][2].equals(" X ") && board[row][4].equals(" X ")){
                    System.out.print("\033[H\033[2J");
                    System.out.flush();
                    System.out.println("Player Wins");
                    userInput.close();
                    createBoard(board);
                    return true;
                }
            }
            else if (board[row][0].equals(" O ")){
                if(board[row][2].equals(" O ") && board[row][4].equals(" O ")){
                    System.out.print("\033[H\033[2J");
                    System.out.flush();
                    System.out.println("Computer Wins");
                    userInput.close();
                    createBoard(board);
                    return true;
                }
            }
        }

        return false;
    }

    public static boolean threeInARowDiagonal(String[][] board){
        //Downward Sloping Diagonal 
        if(board[0][0].equals(" X ")){
            if(board[2][2].equals(" X ") && board[4][4].equals(" X ")){
                System.out.print("\033[H\033[2J");
                System.out.flush();
                System.out.println("Player Wins");
                userInput.close();
                createBoard(board);
                return true;
            }
        }
        if(board[0][0].equals(" O ")){
            if(board[2][2].equals(" O ") && board[4][4].equals(" O ")){
                System.out.print("\033[H\033[2J");
                System.out.flush();
                System.out.println("Computer Wins");
                userInput.close();
                createBoard(board);
                return true;
            }
        }

        //Upward Sloping Diagoanal
        if(board[0][4].equals(" X ")){
            if(board[2][2].equals(" X ") && board[4][0].equals(" X ")){
                System.out.print("\033[H\033[2J");
                System.out.flush();
                System.out.println("Player Wins");
                userInput.close();
                createBoard(board);
                return true;
            }
        }
        if(board[0][4].equals(" O ")){
            if(board[2][2].equals(" O ") && board[4][0].equals(" O ")){
                System.out.print("\033[H\033[2J");
                System.out.flush();
                System.out.println("Computer Wins");
                userInput.close();
                createBoard(board);
                return true;
            }
        }

        return false;
    }

    public static boolean isBoardFilled(String[][] board, boolean gameDone){
        if(gameDone == true){
            return true;
        }
        for(int i = 0; i < invalidInputs.length; i++){
            if(invalidInputs[i].equals("")){
                return false;
            }
        }

        if(gameDone == false){
            System.out.print("\033[H\033[2J");
            System.out.flush();
            System.out.println("IT IS A TIE");
            userInput.close();
            createBoard(board);
        }

        return true;
    }

    public static String[][] createBoard(String[][] board){
        for(int r = 0; r < board.length; r++){
            for(int c = 0; c < board[r].length; c++){
                System.out.print(board[r][c]);
            }
        }

        return board;   
    }
}
