<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Math Notes | Knowledge Hub</title>
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;600&family=Merriweather:wght@400;700&display=swap" rel="stylesheet">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            background: linear-gradient(135deg, #f8f9ff 0%, #e6f0ff 100%);
            min-height: 100vh;
            font-family: 'Inter', sans-serif;
            color: #2c3e50;
            line-height: 1.8;
            padding: 2rem;
        }
        .login-container {
            max-width: 400px;
            margin: 5rem auto;
            padding: 2rem;
            background: rgba(255, 255, 255, 0.95);
            border-radius: 16px;
            box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
            backdrop-filter: blur(8px);
            border: 1px solid rgba(255, 255, 255, 0.3);
            text-align: center;
        }

        .login-container h1 {
            font-family: 'Merriweather', serif;
            font-size: 2rem;
            margin-bottom: 1.5rem;
            color: #2c3e50;
        }

        .login-container input {
            width: 100%;
            padding: 12px;
            margin: 10px 0;
            border: 1px solid #ddd;
            border-radius: 8px;
            font-size: 1rem;
        }

        .login-container button {
            width: 100%;
            padding: 12px;
            background: linear-gradient(135deg, #4a90e2 0%, #6c5ce7 100%);
            border: none;
            border-radius: 8px;
            color: white;
            font-size: 1rem;
            cursor: pointer;
            transition: all 0.3s ease;
            margin-top: 1rem;
        }

        .login-container button:hover {
            transform: translateY(-2px);
            box-shadow: 0 4px 6px rgba(74, 144, 226, 0.3);
        }
        .dashboard-container {
            max-width: 800px;
            margin: 2rem auto;
            padding: 2rem;
            background: rgba(255, 255, 255, 0.95);
            border-radius: 16px;
            box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
            backdrop-filter: blur(8px);
            border: 1px solid rgba(255, 255, 255, 0.3);
            display: none; /* 默认隐藏 */
        }

        .dashboard-container h1 {
            font-family: 'Merriweather', serif;
            font-size: 2rem;
            margin-bottom: 1.5rem;
            color: #2c3e50;
        }

        .stats {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 1rem;
            margin-bottom: 2rem;
        }

        .stat-card {
            background: rgba(255, 255, 255, 0.9);
            padding: 1.5rem;
            border-radius: 12px;
            text-align: center;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }

        .stat-card h3 {
            font-size: 1.2rem;
            margin-bottom: 0.5rem;
            color: #4a5568;
        }

        .stat-card p {
            font-size: 1.5rem;
            font-weight: 600;
            color: #2c3e50;
        }

        .logout-btn, .back-btn {
            background: #ff6b6b;
            border: none;
            border-radius: 8px;
            color: white;
            padding: 12px 24px;
            font-size: 1rem;
            cursor: pointer;
            transition: all 0.3s ease;
            margin: 0.5rem;
        }

        .logout-btn:hover, .back-btn:hover {
            background: #ff4757;
            transform: translateY(-2px);
        }

        .back-btn {
            background: #4a90e2;
        }

        .back-btn:hover {
            background: #357abd;
        }
        @keyframes fadeIn {
            from {
                opacity: 0;
                transform: translateY(20px);
            }
            to {
                opacity: 1;
                transform: translateY(0);
            }
        }

        .login-container, .dashboard-container {
            animation: fadeIn 0.8s ease-out;
        }
    </style>
</head>
<body>
    <div class="login-container" id="loginContainer">
        <h1>Welcome to Math Notes</h1>
        <input type="text" id="username" placeholder="Username" required>
        <input type="password" id="password" placeholder="Password" required>
        <button onclick="login()">Login</button>
        <button class="back-btn" onclick="goBack()">Back to Home</button>
    </div>
    <div class="dashboard-container" id="dashboardContainer">
        <h1>Dashboard</h1>
        <div class="stats">
            <div class="stat-card">
                <h3>Total Notes</h3>
                <p>128</p>
            </div>
            <div class="stat-card">
                <h3>Active Users</h3>
                <p>24</p>
            </div>
            <div class="stat-card">
                <h3>Completed Tasks</h3>
                <p>56</p>
            </div>
        </div>
        <button class="logout-btn" onclick="logout()">Logout</button>
        <button class="back-btn" onclick="goBack()">Back to Home</button>
    </div>

    <script>
        function login() {
            const username = document.getElementById('username').value;
            const password = document.getElementById('password').value;
            if (username === 'admin' && password === '123456') {
                document.getElementById('loginContainer').style.display = 'none';
                document.getElementById('dashboardContainer').style.display = 'block';
            } else {
                alert('Invalid username or password');
            }
        }
        function logout() {
            document.getElementById('dashboardContainer').style.display = 'none';
            document.getElementById('loginContainer').style.display = 'block';
            document.getElementById('username').value = '';
            document.getElementById('password').value = '';
        }
        function goBack() {
            window.location.href = 'javascript:history.back(-1)';
        }
    </script>
</body>
</html>
