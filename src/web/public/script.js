document.addEventListener('DOMContentLoaded', () => {
    const canvas = document.getElementById('mazeCanvas');
    const ctx = canvas.getContext('2d');
    const widthInput = document.getElementById('width');
    const heightInput = document.getElementById('height');
    const fileInput = document.getElementById('file');
    const loadMazeButton = document.getElementById('loadMaze');
    const generateMazeButton = document.getElementById('generateMaze');
    const solveMazeButton = document.getElementById('solveMaze');
    const startXInput = document.getElementById('startX');
    const startYInput = document.getElementById('startY');
    const endXInput = document.getElementById('endX');
    const endYInput = document.getElementById('endY');

    canvas.width = 500;
    canvas.height = 500;

    let mazeWidth, mazeHeight;

    const directions = [
        { dx: 1, dy: 0 }, // Right
        { dx: -1, dy: 0 }, // Left
        { dx: 0, dy: 1 }, // Down
        { dx: 0, dy: -1 } // Up
    ];

    function drawMaze(rightWalls, bottomWalls, solution = []) {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
    
        const cellWidth = (canvas.width - 2 * (mazeWidth - 1)) / mazeWidth;
        const cellHeight = (canvas.height - 2 * (mazeHeight - 1)) / mazeHeight;

        ctx.strokeStyle = 'white';
        ctx.fillStyle = 'white';
        ctx.lineWidth = 2;

        ctx.lineJoin = 'square'; 
        ctx.lineCap = 'square'; 

        ctx.imageSmoothingEnabled = false;
    
        for (let y = 0; y < mazeHeight; y++) {
            for (let x = 0; x < mazeWidth; x++) {
                let cellX = x * (cellWidth + 2);
                let cellY = y * (cellHeight + 2);
    
                // Draw right wall
                if (rightWalls[y][x]) {
                    ctx.beginPath();
                    ctx.moveTo(cellX + cellWidth + 2, cellY);
                    ctx.lineTo(cellX + cellWidth + 2, cellY + cellHeight);
                    ctx.stroke();
                }
    
                // Draw bottom wall
                if (bottomWalls[y][x]) {
                    ctx.beginPath();
                    ctx.moveTo(cellX, cellY + cellHeight + 1);
                    ctx.lineTo(cellX + cellWidth + 1, cellY + cellHeight + 1);
                    ctx.stroke();
                }
    
                // Draw solution path
                if (solution.length > 0 && solution[y][x] === 1) {
                    ctx.fillStyle = 'rgba(163, 40, 56)';
                    ctx.beginPath();
                    ctx.arc(cellX + cellWidth / 2, cellY + cellHeight / 2, Math.min(cellWidth, cellHeight) / 10, 0, 2 * Math.PI);
                    ctx.fill();

                    directions.forEach(dir => {
                        const nx = x + dir.dx;
                        const ny = y + dir.dy;
        
                        if (nx >= 0 && nx < mazeWidth && ny >= 0 && ny < mazeHeight && solution[ny][nx] === 1) {
                            if ((dir.dx === 1 && !rightWalls[y][x]) || (dir.dx === -1 && !rightWalls[ny][nx]) ||
                                (dir.dy === 1 && !bottomWalls[y][x]) || (dir.dy === -1 && !bottomWalls[ny][nx])) {
                                ctx.strokeStyle = 'rgba(163, 40, 56)';
                                ctx.lineWidth = 2;
                                ctx.beginPath();
                                ctx.moveTo(cellX + cellWidth / 2, cellY + cellHeight / 2);
                                ctx.lineTo(cellX + cellWidth / 2 + dir.dx * (cellWidth / 2), cellY + cellHeight / 2 + dir.dy * (cellHeight / 2));
                                ctx.stroke();
                            }
                        }
                    });  
                    
                    ctx.strokeStyle = 'white';
                    ctx.fillStyle = 'white';
                }
            }
        }
    }

    async function loadMaze() {
        if (fileInput.files.length > 0) {
            const file = fileInput.files[0];
            const data = await file.text();
            const [rightWalls, bottomWalls] = parseMazeData(data);
            drawMaze(rightWalls, bottomWalls);
    
            await fetch('/copyMaze', {
                method: 'POST',
                headers: {
                    'Content-Type': 'text/plain'
                },
                body: data
            });
        }
    }

    async function generateMaze() {
        mazeWidth = parseInt(widthInput.value);
        mazeHeight = parseInt(heightInput.value);

        const response = await fetch('/generateMaze', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ width: mazeWidth, height: mazeHeight })
        });

        const { rightWalls, bottomWalls } = await response.json();
        drawMaze(rightWalls, bottomWalls);
    }

    async function solveMaze() {
        const startX = parseInt(startXInput.value);
        const startY = parseInt(startYInput.value);
        const endX = parseInt(endXInput.value);
        const endY = parseInt(endYInput.value);

        if (startX <= mazeWidth && startY <= mazeHeight && endX <= mazeWidth && endY <= mazeHeight) {
            const response = await fetch('/solveMaze', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ startX, startY, endX, endY })
            });

            const { rightWalls, bottomWalls, solution } = await response.json();
            drawMaze(rightWalls, bottomWalls, solution);
        }
    }

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

        mazeWidth = width;
        mazeHeight = height;

        return [rightWalls, bottomWalls];
    }

    loadMazeButton.addEventListener('click', loadMaze);
    generateMazeButton.addEventListener('click', generateMaze);
    solveMazeButton.addEventListener('click', solveMaze);

    document.getElementById('file-input-button').addEventListener('click', function() {
        document.getElementById('file').click();
    });

    document.getElementById('file').addEventListener('change', function(event) {
        const fileInput = event.target;
        const fileName = fileInput.files[0] ? fileInput.files[0].name : 'Choose file';
        document.getElementById('file-input-button').textContent = fileName;
    });
});