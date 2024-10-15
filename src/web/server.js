const express = require('express');
const { exec } = require('child_process');
const bodyParser = require('body-parser');
const fs = require('fs');
const app = express();
const port = 3000;

app.use(express.static('public'));
app.use(bodyParser.json());
app.use(bodyParser.text());

const MAZE_FILE = 'maze.txt';
const SOLUTION_FILE = 'maze_solution.txt';

app.post('/generateMaze', (req, res) => {
    const { width, height } = req.body;
    exec(`../build/program -m -o ${MAZE_FILE} -w ${width} -h ${height} -q`, (error, stdout, stderr) => {
        if (error) {
            res.status(500).send(error.message);
            return;
        }
        const mazeData = fs.readFileSync(MAZE_FILE, 'utf8');
        const [rightWalls, bottomWalls] = parseMazeData(mazeData);
        res.json({ rightWalls, bottomWalls });
    });
});

app.post('/solveMaze', (req, res) => {
    const { startX, startY, endX, endY } = req.body;
    exec(`../build/program -m ${MAZE_FILE} -s ${startX} ${startY} -e ${endX} ${endY} -q`, (error, stdout, stderr) => {
        if (error) {
            res.status(500).send(error.message);
            return;
        }
        const mazeData = fs.readFileSync(MAZE_FILE, 'utf8');
        const solutionData = fs.readFileSync(SOLUTION_FILE, 'utf8');
        const [rightWalls, bottomWalls] = parseMazeData(mazeData);
        const solution = parseSolutionData(solutionData);
        res.json({ rightWalls, bottomWalls, solution });
    });
});

app.post('/copyMaze', (req, res) => {
    const data = req.body;
    fs.writeFile(MAZE_FILE, data, (err) => {
        if (err) {
            console.error('File write error:', err);
            res.status(500).send('File write error');
        } else {
            console.log('File copied successfully:', MAZE_FILE);
            res.status(200).send('File copied successfully');
        }
    });
});

function parseMazeData(data) {
    const lines = data.trim().split('\n');
    const [height, width] = lines[0].split(' ').map(Number);
    const rightWalls = [];
    const bottomWalls = [];

    for (let i = 1; i <= height; i++) {
        rightWalls.push(lines[i].split(' ').map(Number));
    }

    for (let i = height + 2; i < lines.length; i++) {
        bottomWalls.push(lines[i].split(' ').map(Number));
    }

    return [rightWalls, bottomWalls];
}

function parseSolutionData(data) {
    const lines = data.trim().split('\n');
    const [height, width] = lines[0].split(' ').map(Number);
    const solution = [];

    for (let i = 1; i <= height; i++) {
        solution.push(lines[i].split(' ').map(Number));
    }

    return solution;
}

app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});