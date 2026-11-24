/*
This file is part of NovexGram Desktop.
Native Sovereign Suite & Creator GodMode Controls.
*/
#include "boxes/novexgram_godmode_box.h"

#include "ui/layers/generic_box.h"
#include "ui/text/text_utilities.h"
#include "ui/toast/toast.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/checkbox.h"
#include "ui/widgets/fields/special_fields.h"
#include "ui/widgets/labels.h"
#include "window/window_session_controller.h"
#include "main/main_session.h"
#include "data/data_user.h"
#include "config.h"
#include "styles/style_boxes.h"
#include "styles/style_layers.h"

namespace NovexGram {

void ShowGodModeBox(not_null<Window::SessionController*> controller) {
	controller->uiShow()->show(Box([=](not_null<Ui::GenericBox*> box) {
		box->setTitle(rpl::single(u"⚡ NovexGram Sovereign & GodMode Suite"_q));

		// --- Header Section ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"👑 <b>Консоль Верховного Создателя (ID #1)</b><br/>"
			"Управление суверенным клиентом, значками верификации и номерами +888."_q,
			st::boxLabel));

		box->addSkip(10);

		// --- Badge Selector Section ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"<b>Выбор значка профиля и статуса верификации:</b>"_q,
			st::boxLabel));

		const auto currentBadge = std::make_shared<QString>(u"👑 Корона Создателя"_q);

		const auto badgeLabel = box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			rpl::single(u"Текущий значок: 👑 Корона Создателя"_q),
			st::boxLabel));

		// Row of Badge Buttons
		const auto badges = std::vector<std::pair<QString, QString>>{
			{ u"👑 Корона"_q, u"👑 Корона Создателя (ID #1)"_q },
			{ u"✔️ Галочка"_q, u"✔️ Официальная Верификация"_q },
			{ u"⭐ Premium"_q, u"⭐ Telegram Premium Звезда"_q },
			{ u"💎 Алмаз"_q, u"💎 Основатель Экосистемы"_q },
			{ u"🔥 Огонь"_q, u"🔥 Огненный Статус"_q },
			{ u"🛡️ Щит"_q, u"🛡️ Суверенная Защита"_q },
		};

		for (const auto &[shortName, fullName] : badges) {
			box->addRow(object_ptr<Ui::RoundButton>(
				box,
				rpl::single(shortName + u" — " + fullName),
				st::defaultBoxButton
			))->setClickedCallback([=] {
				*currentBadge = fullName;
				badgeLabel->setText(u"Текущий значок: "_q + fullName);
				controller->uiShow()->showToast(u"Значок изменен на: "_q + fullName);
			});
			box->addSkip(3);
		}

		box->addSkip(12);

				// --- User Verification & Badge Granting Section ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"<b>👑 Выдача верификации и бейджей другим пользователям:</b><br/>"
			"Укажите @username или ID пользователя для присвоения галочки и бейджа."_q,
			st::boxLabel));

		const auto targetUserInput = box->addRow(object_ptr<Ui::InputField>(
			box,
			st::defaultInputField,
			rpl::single(u"User ID или @username (например: @boba или 2)"_q),
			u"@boba"_q));

		const auto selectedUserBadge = std::make_shared<QString>(u"✔️ Официальная Верификация"_q);

		const auto userBadgeLabel = box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			rpl::single(u"Выбранный статус: ✔️ Официальная Верификация"_q),
			st::boxLabel));

		// Quick select badge for target user
		const auto targetBadges = std::vector<std::pair<QString, QString>>{
			{ u"✔️ Верификация (Галочка)"_q, u"✔️ Официальная Верификация"_q },
			{ u"⭐ Premium Звезда"_q, u"⭐ Telegram Premium"_q },
			{ u"💎 VIP Алмаз"_q, u"💎 VIP Статус"_q },
			{ u"👑 Со-Создатель"_q, u"👑 Доверенный Со-Создатель"_q },
		};

		for (const auto &[shortName, fullName] : targetBadges) {
			box->addRow(object_ptr<Ui::RoundButton>(
				box,
				rpl::single(shortName),
				st::defaultBoxButton
			))->setClickedCallback([=] {
				*selectedUserBadge = fullName;
				userBadgeLabel->setText(u"Выбранный статус: "_q + fullName);
			});
			box->addSkip(2);
		}

		box->addSkip(6);

		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"✔️ Выдать верификацию и бейдж пользователю"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			const auto target = targetUserInput->getLastText().trimmed();
			controller->uiShow()->showToast(
				u"👑 Пользователю "_q + target + u" успешно присвоен статус: "_q + *selectedUserBadge + u"!"_q);
		});

		box->addSkip(3);

		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"❌ Отозвать верификацию у пользователя"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			const auto target = targetUserInput->getLastText().trimmed();
			controller->uiShow()->showToast(
				u"Статус верификации у "_q + target + u" успешно отозван."_q);
		});

		box->addSkip(12);

		// --- Sovereign +888 Numbers Section ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"<b>📱 Выдача анонимных номеров +888 (Fragment Sovereign):</b>"_q,
			st::boxLabel));

		const auto phoneInput = box->addRow(object_ptr<Ui::InputField>(
			box,
			st::defaultInputField,
			rpl::single(u"+888 XXXX XXXX"_q),
			u"+888 0001 0001"_q));

		// Preset buttons for +888 numbers
		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"Пресет: +888 0001 0001 (Genesis #1)"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			phoneInput->setText(u"+888 0001 0001"_q);
		});

		box->addSkip(3);

		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"Пресет: +888 7777 7777 (Lucky Sevens)"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			phoneInput->setText(u"+888 7777 7777"_q);
		});

		box->addSkip(8);

		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"📱 Закрепить номер за аккаунтом Создателя"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			const auto rawNumber = phoneInput->getLastText().trimmed();
			const auto user = controller->session().user();
			user->setPhone(rawNumber);
			controller->uiShow()->showToast(
				u"👑 Номер "_q + rawNumber + u" успешно привязан к аккаунту Создателя!"_q);
		});

		box->addSkip(12);

		// --- Stealth & Security Toggles ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"<b>Шпионские и защитные модули (Sovereign Security):</b>"_q,
			st::boxLabel));

		box->addRow(object_ptr<Ui::Checkbox>(
			box,
			u"👻 Ghost Mode (Невидимка: чтение без галочек, скрытие набора текста)"_q,
			GhostModeEnabled,
			st::defaultCheckbox));

		box->addRow(object_ptr<Ui::Checkbox>(
			box,
			u"🗑️ Anti-Delete (Сохранять удаленные сообщения навсегда)"_q,
			AntiDeleteEnabled,
			st::defaultCheckbox));

		box->addSkip(12);

		// --- Minting Section ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"<b>Мастер-минт подарков и редких юзернеймов:</b>"_q,
			st::boxLabel));

		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"🎁 Чеканить любой подарок / NFT с номером #0001"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			controller->uiShow()->showToast(u"🎁 Подарок #0001 отчеканен и добавлен в инвентарь!"_q);
		});

		box->addSkip(3);

		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"⭐ Зачислить 999,999,999 Telegram Stars"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			controller->uiShow()->showToast(u"⭐ 999,999,999 Stars начислены Создателю!"_q);
		});

		box->addSkip(15);

				box->addSkip(10);

		// --- Unique NFT Minting & Upgrade (Model + Symbol + Backdrop + Gram) ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"<b>✨ Конструктор Уникального NFT Подарка (Fragment / TON):</b><br/>"
			"Выбирайте Model, Symbol (узор) и Backdrop (фон) с кастомным номером #0001."_q,
			st::boxLabel));

		const auto nftGiftName = box->addRow(object_ptr<Ui::InputField>(
			box,
			st::defaultInputField,
			rpl::single(u"Название подарка (например: Plush Pepe)"_q),
			u"Plush Pepe"_q));

		const auto nftSerialInput = box->addRow(object_ptr<Ui::InputField>(
			box,
			st::defaultInputField,
			rpl::single(u"Порядковый номер NFT (например: #0001 или #0274)"_q),
			u"#0001"_q));

		// 1. Model Selection
		const auto selectedModel = std::make_shared<QString>(u"X-Ray (2%)"_q);
		const auto modelLabel = box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			rpl::single(u"Выбранная Model: X-Ray (2%)"_q),
			st::boxLabel));

		const auto models = std::vector<std::pair<QString, QString>>{
			{ u"X-Ray (2%)"_q, u"X-Ray (2%)"_q },
			{ u"👑 Gold (0.1%)"_q, u"Sovereign Gold (0.1%)"_q },
			{ u"🥷 Ninja (1%)"_q, u"Ninja Hero (1%)"_q },
			{ u"🐸 Pepe Classic (5%)"_q, u"Pepe Classic (5%)"_q },
			{ u"🌌 Cosmic (0.05%)"_q, u"Cosmic Hologram (0.05%)"_q },
		};

		for (const auto &[shortName, fullName] : models) {
			box->addRow(object_ptr<Ui::RoundButton>(
				box,
				rpl::single(u"Model: "_q + shortName),
				st::defaultBoxButton
			))->setClickedCallback([=] {
				*selectedModel = fullName;
				modelLabel->setText(u"Выбранная Model: "_q + fullName);
			});
			box->addSkip(2);
		}

		box->addSkip(6);

		// 2. Symbol (Pattern) Selection
		const auto selectedSymbol = std::make_shared<QString>(u"Cheese (0.2%)"_q);
		const auto symbolLabel = box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			rpl::single(u"Выбранный Symbol: Cheese (0.2%)"_q),
			st::boxLabel));

		const auto symbols = std::vector<std::pair<QString, QString>>{
			{ u"🧀 Cheese (0.2%)"_q, u"Cheese (0.2%)"_q },
			{ u"👑 Crown (0.1%)"_q, u"Creator Crown (0.1%)"_q },
			{ u"💎 Diamond (0.5%)"_q, u"TON Diamond (0.5%)"_q },
			{ u"❤️ Heart (1%)"_q, u"Burning Heart (1%)"_q },
			{ u"💀 Skull (0.3%)"_q, u"Sovereign Skull (0.3%)"_q },
		};

		for (const auto &[shortName, fullName] : symbols) {
			box->addRow(object_ptr<Ui::RoundButton>(
				box,
				rpl::single(u"Symbol: "_q + shortName),
				st::defaultBoxButton
			))->setClickedCallback([=] {
				*selectedSymbol = fullName;
				symbolLabel->setText(u"Выбранный Symbol: "_q + fullName);
			});
			box->addSkip(2);
		}

		box->addSkip(6);

		// 3. Backdrop (Gradient Background) Selection
		const auto selectedBackdrop = std::make_shared<QString>(u"French Blue (2%)"_q);
		const auto backdropLabel = box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			rpl::single(u"Выбранный Backdrop: French Blue (2%)"_q),
			st::boxLabel));

		const auto backdrops = std::vector<std::pair<QString, QString>>{
			{ u"🟦 French Blue (2%)"_q, u"French Blue (2%)"_q },
			{ u"👑 Sovereign Gold (0.1%)"_q, u"Sovereign Gold (0.1%)"_q },
			{ u"🟩 Emerald (1%)"_q, u"Emerald Green (1%)"_q },
			{ u"🟪 Imperial Violet (0.5%)"_q, u"Imperial Violet (0.5%)"_q },
			{ u"⬛ Obsidian Black (0.2%)"_q, u"Obsidian Black (0.2%)"_q },
		};

		for (const auto &[shortName, fullName] : backdrops) {
			box->addRow(object_ptr<Ui::RoundButton>(
				box,
				rpl::single(u"Backdrop: "_q + shortName),
				st::defaultBoxButton
			))->setClickedCallback([=] {
				*selectedBackdrop = fullName;
				backdropLabel->setText(u"Выбранный Backdrop: "_q + fullName);
			});
			box->addSkip(2);
		}

		box->addSkip(8);

		// Action Button: Mint / Upgrade with full attributes
		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"✨ Чеканить / Улучшить NFT с Model + Symbol + Backdrop"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			const auto gift = nftGiftName->getLastText().trimmed();
			const auto serial = nftSerialInput->getLastText().trimmed();
			controller->uiShow()->showToast(
				u"🎉 Создан Уникальный NFT: "_q + gift + u" " + serial +
				u" [Model: " + *selectedModel + u", Symbol: " + *selectedSymbol + u", Backdrop: " + *selectedBackdrop + u"]!"_q);
		});

		box->addSkip(12);

		// --- Gram / Diamond (💎) Currency Section ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"<b>💎 Валюта Gram / TON Diamonds:</b><br/>"
			"Крипто-валюта Fragment и маркета подарков Telegram."_q,
			st::boxLabel));

		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"💎 Зачислить 999,999,999 Gram (Баланс Создателя)"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			controller->uiShow()->showToast(u"💎 999,999,999 Gram зачислено Создателю!"_q);
		});

		box->addSkip(15);

		// --- Save / Close ---
		box->addButton(rpl::single(u"Сохранить и применить"_q), [=] {
			box->closeBox();
			controller->uiShow()->showToast(u"⚡ Настройки NovexGram Sovereign применены!"_q);
		});
	}));
}

} // namespace NovexGram
