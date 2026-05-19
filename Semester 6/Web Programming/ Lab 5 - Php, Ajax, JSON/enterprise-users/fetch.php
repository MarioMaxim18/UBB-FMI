<?php
require 'db.php';

$role = isset($_GET['role']) ? trim($_GET['role']) : '';
$name = isset($_GET['name']) ? trim($_GET['name']) : '';

$allowedRoles = ['Admin', 'Manager', 'Developer'];
if ($role !== '' && !in_array($role, $allowedRoles, true)) {
    header('Content-Type: application/json');
    echo json_encode([]);
    exit;
}

if (strlen($name) > 100) {
    $name = substr($name, 0, 100);
}

$query = "SELECT * FROM users WHERE 1=1";
$params = [];

if (!empty($role)) {
    $query .= " AND role = :role";
    $params['role'] = $role;
}

if (!empty($name)) {
    $query .= " AND name LIKE :name";
    $params['name'] = '%' . $name . '%';
}

$query .= " ORDER BY id DESC";

$stmt = $pdo->prepare($query);
$stmt->execute($params);
$users = $stmt->fetchAll();

header('Content-Type: application/json');
echo json_encode($users);
?>
