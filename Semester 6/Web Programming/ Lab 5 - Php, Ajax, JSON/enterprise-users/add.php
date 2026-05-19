<?php
require 'db.php';
require_once 'validation.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $name = isset($_POST['name']) ? trim($_POST['name']) : '';
    $username = isset($_POST['username']) ? trim($_POST['username']) : '';
    $password = isset($_POST['password']) ? trim($_POST['password']) : '';
    $age = isset($_POST['age']) && $_POST['age'] !== '' ? (int) $_POST['age'] : 0;
    $role = isset($_POST['role']) ? trim($_POST['role']) : '';
    $profile = isset($_POST['profile']) ? trim($_POST['profile']) : '';
    $email = isset($_POST['email']) ? trim($_POST['email']) : '';
    $webpage = isset($_POST['webpage']) ? trim($_POST['webpage']) : '';

    $err = validate_user_input([
        'name' => $name,
        'username' => $username,
        'password' => $password,
        'age' => $age,
        'role' => $role,
        'profile' => $profile,
        'email' => $email,
        'webpage' => $webpage,
    ], true);

    if ($err !== null) {
        echo json_encode(['status' => 'error', 'message' => $err]);
        exit;
    }

    $sql = "INSERT INTO users (name, username, password, age, role, profile, email, webpage) 
            VALUES (:name, :username, :password, :age, :role, :profile, :email, :webpage)";
    $stmt = $pdo->prepare($sql);

    try {
        $result = $stmt->execute([
            'name' => $name,
            'username' => $username,
            'password' => $password,
            'age' => $age,
            'role' => $role,
            'profile' => $profile,
            'email' => $email,
            'webpage' => $webpage,
        ]);

        if ($result) {
            echo json_encode(['status' => 'success', 'message' => 'User added successfully.']);
        } else {
            echo json_encode(['status' => 'error', 'message' => 'Failed to add user.']);
        }
    } catch (\PDOException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Database error: ' . $e->getMessage()]);
    }
}
?>
