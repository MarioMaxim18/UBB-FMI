<?php
require 'db.php';
require_once 'validation.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $id = isset($_POST['id']) ? (int) $_POST['id'] : 0;
    $name = isset($_POST['name']) ? trim($_POST['name']) : '';
    $username = isset($_POST['username']) ? trim($_POST['username']) : '';
    $password = isset($_POST['password']) ? trim($_POST['password']) : '';
    $age = isset($_POST['age']) && $_POST['age'] !== '' ? (int) $_POST['age'] : 0;
    $role = isset($_POST['role']) ? trim($_POST['role']) : '';
    $profile = isset($_POST['profile']) ? trim($_POST['profile']) : '';
    $email = isset($_POST['email']) ? trim($_POST['email']) : '';
    $webpage = isset($_POST['webpage']) ? trim($_POST['webpage']) : '';

    if ($id <= 0) {
        echo json_encode(['status' => 'error', 'message' => 'Invalid user ID.']);
        exit;
    }

    $err = validate_user_input([
        'name' => $name,
        'username' => $username,
        'password' => $password,
        'age' => $age,
        'role' => $role,
        'profile' => $profile,
        'email' => $email,
        'webpage' => $webpage,
    ], false);

    if ($err !== null) {
        echo json_encode(['status' => 'error', 'message' => $err]);
        exit;
    }

    $updatePassword = $password !== '';

    if ($updatePassword) {
        $sql = "UPDATE users SET name=:name, username=:username, password=:password, age=:age, 
                role=:role, profile=:profile, email=:email, webpage=:webpage WHERE id=:id";
        $params = [
            'id' => $id,
            'name' => $name,
            'username' => $username,
            'password' => $password,
            'age' => $age,
            'role' => $role,
            'profile' => $profile,
            'email' => $email,
            'webpage' => $webpage,
        ];
    } else {
        $sql = "UPDATE users SET name=:name, username=:username, age=:age, 
                role=:role, profile=:profile, email=:email, webpage=:webpage WHERE id=:id";
        $params = [
            'id' => $id,
            'name' => $name,
            'username' => $username,
            'age' => $age,
            'role' => $role,
            'profile' => $profile,
            'email' => $email,
            'webpage' => $webpage,
        ];
    }

    $stmt = $pdo->prepare($sql);

    try {
        $result = $stmt->execute($params);

        if ($result) {
            echo json_encode(['status' => 'success', 'message' => 'User updated successfully.']);
        } else {
            echo json_encode(['status' => 'error', 'message' => 'Failed to update user.']);
        }
    } catch (\PDOException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Database error: ' . $e->getMessage()]);
    }
}
?>
